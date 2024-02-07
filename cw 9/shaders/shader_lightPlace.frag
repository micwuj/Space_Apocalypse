#version 430 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BloomColor;  

in vec2 vecTex;

uniform sampler2D colorTexture;
uniform float exposition;

out vec4 outColor;

void main()
{
    vec3 color = texture2D(colorTexture, vecTex).xyz;
	outColor = vec4(vec3(1.0) - exp(-color*exposition),1)*1.2;

    FragColor = outColor;
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.1)
        BloomColor = vec4(FragColor.rgb, 1.0);
    else
        BloomColor = vec4(0.0, 0.0, 0.0, 1.0);
}
