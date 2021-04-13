#include "hblk_crypto.h"
/**
 * sha256 - compute the hash of a sequence of bytes
 * @s: Sequence of bytes to be hashed
 * @len: Bytes to hash
 * @digest: array to store resulting hash in
 *
 * Return: pointer to digest, NULL on error
 */
uint8_t * sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]){
        SHA256_CTX ctx;
        if(!digest)
                return NULL;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, s, len);
        SHA256_Final(digest,&ctx);
        return digest;
}
