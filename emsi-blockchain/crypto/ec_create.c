#include "hblk_crypto.h"
EC_KEY *ec_create(void)
{
        EC_KEY * ec_key;
        ec_key = EC_KEY_new_by_curve_name(EC_CURVE);
        if (!ec_key)
                return NULL;
        if (!EC_KEY_generate_key(ec_key))
        {
                EC_KEY_free(ec_key);
                return NULL;
        }
        return ec_key;
}
