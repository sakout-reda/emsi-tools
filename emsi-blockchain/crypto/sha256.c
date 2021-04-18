#include <stdint.h>
#include "hblk_crypto.h"
uint8_t * sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]){
        SHA256_CTX ctx;
        if(!digest)
                return NULL;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, s, len);
        SHA256_Final(digest,&ctx);
        return digest;
}
