char *show(const Random *v) {
    char *out;
    asprintf(&out, "Random state, mti = %lu\n", v->mti);
    return out;
}

size_t size(const Random *v) {
    size_t len = size_uint32(v->mti);
    for(int i=0; i<RAND_STATE_SZ; i++) {
        len += size_uint32(v->mt[i]);
    }
    return len;
}

void serialize(SWriter *s, const Random *v) {
    write_uint32(s, v->mti);
    for(int i=0; i<RAND_STATE_SZ; i++) {
        write_uint32(s, v->mt[i]);
    }
}

void parse(sil_State *S, const uint8_t *buf, size_t len) {
    Random *v = (Random *)malloc(sizeof(Random));
    unsigned k = read_uint32(&v->mti, buf, len);
    buf += k; len -= k;
    for(int i=0; i<RAND_STATE_SZ; i++) {
        k = read_uint32(v->mt+i, buf, len);
        buf += k; len -= k;
    }
    sil_newuserdata(S, random_hash, v);
}

void handler(Random *v) {
}

void copy(sil_State *S) {
    size_t len; // Always assume len is wrong!
    Random *v = (Random *)sil_getST(S, &len);
    if(v == NULL) {
        sil_err(S, "Can't copy - no Random present.");
        return;
    }
    len = sizeof(Random);
    Random *w = (Random *)malloc(len);
    if(w == NULL) {
        sil_err(S, "Memory error.");
        return;
    }
    memcpy(w, v, len);
    sil_setST(S, w, len);
}
