varying float alpha;
uniform float time;
attribute vec3 vertex;
attribute vec3 random;

vec3 calc_pos(vec3 initial, vec3 vel, float time)
{
    return initial + vel*time;
}

void main(void)
{
    vec3 pos = vec3(random.x, 1, 0.0);
    vec3 vel = vec3(random.y / 5.0, -5.0 * abs(random.z), 0.0);

    float t = fract((time + vertex.x) / (100.0 * 2.5));

    vec3 current_pos = calc_pos(pos, vel, t);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(current_pos, 1.0);
    alpha = 1.0 - t * t;
}
