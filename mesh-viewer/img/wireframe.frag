#version 330 core


uniform struct LightInfo {
    vec4 position;
    vec3 intensity;
    vec4 color;
} light;

uniform struct LineInfo {
    float width;
    vec4 color;
} line;

uniform vec3 ka;            // Ambient reflectivity
uniform vec3 kd;            // Diffuse reflectivity
uniform vec3 ks;            // Specular reflectivity
uniform float shininess;    // Specular shininess factor

uniform int mode;           // 1 to render lines only
                            // 2 to render the inside of mesh
flat in vec3 vViewPos;
in WireframeVertex {
    vec3 position;
    vec3 normal;
    noperspective vec4 edgeA;
    noperspective vec4 edgeB;
    flat int configuration;
} fs_in;

out vec4 fragColor;
uniform sampler2D texture1;
vec3 normals(vec3 pos)
{
    vec3 fdx = dFdx(pos);
    vec3 fdy = dFdy(pos);
    return normalize(cross(fdx, fdy));
}

flat in vec4 polygon_color;

vec3 adsModel( const in vec3 pos, const in vec3 n )
{

    vec3 normal = normals(vViewPos);
    float theta = dot(normal, vec3( pos ) / n);

    // Calculate the vector from the light to the fragment
    vec3 s = normalize( vec3( light.position ) - pos );

    // Calculate the vector from the fragment to the eye position (the
    // origin since this is in "eye" or "camera" space
    vec3 v = normalize( -pos );

    // Refleft the light beam using the normal at this fragment
    vec3 r = reflect( -s, n );

    // Calculate the diffus component
    vec3 diffuse = vec3( max( dot( s, n ), 0.0 ) );

    // Calculate the specular component
    vec3 specular = vec3( pow( max( dot( r, v ), 0.0 ), shininess ) );

    // Combine the ambient, diffuse and specular contributions
    return light.intensity *( (kd * diffuse) + (ks * specular) + ka);
}

vec4 shadeLine( const in vec4 color )
{
    // Find the smallest distance between the fragment and a triangle edge
    float d;
    if ( fs_in.configuration == 0 )
    {
        // Common configuration
        d = min( fs_in.edgeA.x, fs_in.edgeA.y );
        d = min( d, fs_in.edgeA.z );
    }
    else
    {
        // Handle configuration where screen space projection breaks down
        // Compute and compare the squared distances
        vec2 AF = gl_FragCoord.xy - fs_in.edgeA.xy;
        float sqAF = dot( AF, AF );
        float AFcosA = dot( AF, fs_in.edgeA.zw );
        d = abs( sqAF - AFcosA * AFcosA );

        vec2 BF = gl_FragCoord.xy - fs_in.edgeB.xy;
        float sqBF = dot( BF, BF );
        float BFcosB = dot( BF, fs_in.edgeB.zw );
        d = min( d, abs( sqBF - BFcosB * BFcosB ) );

        // Only need to care about the 3rd edge for some configurations.
        if ( fs_in.configuration == 1 || fs_in.configuration == 2 || fs_in.configuration == 4 )
        {
            float AFcosA0 = dot( AF, normalize( fs_in.edgeB.xy - fs_in.edgeA.xy ) );
            d = min( d, abs( sqAF - AFcosA0 * AFcosA0 ) );
        }

        d = sqrt( d );
    }

    // Blend between line color and phong color
    float mixVal;
    if (mode == 0)
    {
        mixVal = 0.0;
    }
    else
    {
        if ( d < line.width)
        {
            mixVal = 1.0;
        }
        else if ( d > line.width)
        {
            if (mode == 1)
                discard;
            else
                mixVal = 0.0;
        }
        else
        {
            float x = d - ( line.width);
            mixVal = exp2( -2.0 * ( x * x ) );
        }
    }

    return mix( color, line.color, mixVal );
}



void main()
{
    vec3 normal = normals(vViewPos);
    float theta = dot(normal, vec3( light.position ) / length(normal));
    vec3 gray = vec3(0.9, 0.9, 0.9);

    // Calculate the color from the phong model
    vec4 color = vec4( adsModel( fs_in.position, normalize( fs_in.normal )), 1.0)  * light.color;
    fragColor = shadeLine( color ) ;
    //fragColor = vec4(gray * theta, 1.0);
}
