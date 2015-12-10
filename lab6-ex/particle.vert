varying float alpha;
uniform float time;
attribute vec3 vertex;

float atten(float d)
{
    return 1.0/(0.001 + d*d);
}

vec3 calc_pos(vec3 initial, vec3 vel, float time)
{
    return initial + vel*time;
}

vec3 random_vector(float param)
{
    return vec3(sin(param), cos(param*param), sin(param) * exp(cos(param) * sin(param)));
}

void main(void)
{
    vec3 rnd = random_vector(vertex.x);
    vec3 pos = vec3(rnd.y, 1, 0.0);
    vec3 vel = vec3(rnd.z/5.0, -5.0 * abs(rnd.x), 0.0);

    float t = fract((time + vertex.x) / (100.0 * 2.5));

    vec3 current_pos = calc_pos(pos, vel, t);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(current_pos, 1.0);
    alpha = 1.0 - t * t;
}
