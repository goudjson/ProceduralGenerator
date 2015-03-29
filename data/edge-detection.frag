#version 130varying vec2 pxl_texture;uniform sampler2D pg_texture;uniform float pg_width;uniform float pg_height;void main(){	mat3 G[2];	G[0] = mat3( 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 );	g[1] = mat3( 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0 );	mat3 G2[9];	G2[0] = 1.0/(2.0*sqrt(2.0)) * mat3( 1.0, sqrt(2.0), 1.0, 0.0, 0.0, 0.0, -1.0, -sqrt(2.0), -1.0 );	G2[1] = 1.0/(2.0*sqrt(2.0)) * mat3( 1.0, 0.0, -1.0, sqrt(2.0), 0.0, -sqrt(2.0), 1.0, 0.0, -1.0 );	G2[2] = 1.0/(2.0*sqrt(2.0)) * mat3( 0.0, -1.0, sqrt(2.0), 1.0, 0.0, -1.0, -sqrt(2.0), 1.0, 0.0 );	G2[3] = 1.0/(2.0*sqrt(2.0)) * mat3( sqrt(2.0), -1.0, 0.0, -1.0, 0.0, 1.0, 0.0, 1.0, -sqrt(2.0) );	G2[4] = 1.0/2.0 * mat3( 0.0, 1.0, 0.0, -1.0, 0.0, -1.0, 0.0, 1.0, 0.0 );	G2[5] = 1.0/2.0 * mat3( -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0 );	G2[6] = 1.0/6.0 * mat3( 1.0, -2.0, 1.0, -2.0, 4.0, -2.0, 1.0, -2.0, 1.0 );	G2[7] = 1.0/6.0 * mat3( -2.0, 1.0, -2.0, 1.0, 4.0, 1.0, -2.0, 1.0, -2.0 );	G2[8] = 1.0/3.0 * mat3( 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 );	vec2 uv = pxl_texture.xy;	vec3 tc = vec3(1.0, 0.0, 0.0);	float vx_offset = 0.333;	float vx_offset2 = 0.667;		if (uv.x < (vx_offset-0.005))	{		mat3 I;		float cnv[2];		vec3 sample;				for (int i=0; i<3; i++)		{			for (int j=0; j<3; j++)			{				sample = texelFetch( pg_texture, ivec2(gl_FragCoord.xy) + ivec2(i-1,j-1), 0).rgb;				I[i][j] = length(sample);			}		}				for (int i=0; i<2; i++)		{			float dp3 = dot(G[i][0], I[0]) + dot(G[i][1], I[1]) + dot(G[i][2], I[2]);			cnv[i] = dp3 * dp3;		}				tc = vec3(0.5 * sqrt(cnv[0]*cnv[0]+cnv[1]*cnv[1]));	}	else if ((uv.x >= (vx_offset+0.005)) && (uv.x < (vx_offset2-0.005)))	{		mat3 I;		float cnv[9];		vec3 sample;		int i, j;		for (i=0; i<3; i++)		{			for (j=0; j<3; j++)			{				sample = texelFetch(pg_texture, ivec2(gl_FragCoord.xy) + ivec2(i-1,j-1), 0).rgb;				I[i][j] = length(sample);			}		}		for (i=0; i<9; i++)		{			float dp3 = dot(G2[i][0], I[0]) + dot(G2[i][1], I[1]) + dot(G2[i][2], I[2]);			cnv[i] = dp3 * dp3;		}				float M = (cnv[4] + cnv[5]) + (cnv[6] + cnv[7]);		float S = (cnv[0] + cnv[1]) + (cnv[2] + cnv[3]) + (cnv[4] + cnv[5]) + (cnv[6] + cnv[7]) + cnv[8];		tc = vec3(sqrt(M/S));	}	else if (uv.x>=(vx_offset2+0.005))	{		tc = texture2D(pg_texture, uv).rgb;	}		gl_FragColor = vec4(tc, 1.0);}