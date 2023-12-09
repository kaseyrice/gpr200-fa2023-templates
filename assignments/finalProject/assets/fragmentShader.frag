#version 450
	out vec4 FragColor;
    out vec4 color;
	uniform vec3 _Color;
	uniform float _Brightness;
    uniform float iTime;
	in vec2 UV;
    in vec2 TexCoords;
    uniform sampler2D image;
    uniform vec3 spriteColor;

    float circleSDF(vec2 p, float r)
    {
        return length(p)-r;
    }

    void mainImage( out vec4 fragColor, in vec2 fragCoord )
    {       
        //vec2 uv = fragCoord/iResolution.xy;

        //Sine wave allowing colors to change.
        float t = sin(fragCoord.y+sin(-1.0 + iTime));
    
        //Sky color.
        vec3 skyColor = mix(vec3(0.8, 0.5, 0.0), vec3(0.75, 0.0, 0.0), t);
    
        //Create circle representing the sun.
        vec2 sunPos = vec2(cos(-1.0),sin(2.0 + iTime));
        float sunRadius = 0.1;
        float sun = circleSDF(fragCoord - sunPos, sunRadius);
        sun = smoothstep(-0.05,0.05,sun);
        
        //Create a changing color for the sun.
        vec3 sunColor = mix(vec3(1.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), 5.0*t);
    
        //Add sun to the sky.
        skyColor = mix(sunColor, skyColor, sun);
    
        //Creating shape for hills.
        float hills = 1.0 - step(sin(fragCoord.x+iTime) * 0.2 + 0.3, fragCoord.y);
    
        //Add hills to the landscape.
        skyColor = mix(skyColor, vec3(0.0, 0.2, 0.0), hills);
    
        //Output the entire landscape (sky, sun, hills).
        fragColor = vec4(skyColor, 1.0);
    }

	void main()
    {
		FragColor = vec4(UV, 0.0, 1.0);
        mainImage(FragColor, UV);
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
	}
