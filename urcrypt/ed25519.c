#include "urcrypt.h"
#include <string.h>
#include <ed25519.h>

void
urcrypt_ed_puck(const uint8_t seed[32],
                uint8_t out[32])
{
  uint8_t secret[64];
  ed25519_create_keypair(out, secret, seed);
}

void
urcrypt_ed_shar(const uint8_t public[32],
                const uint8_t seed[32],
                uint8_t out[32])
{
  uint8_t self[32], exp[64];

  memset(self, 0, 32);
  memset(exp, 0, 64);
  memset(out, 0, 32);

  ed25519_create_keypair(self, exp, seed);
  ed25519_key_exchange(out, public, exp);
}

void
urcrypt_ed_sign_raw(const uint8_t *message,
                size_t length,
                const uint8_t public[32],
		const uint8_t private[64],
                uint8_t out[64])
{
  ed25519_sign(out, message, length, public, private);
}

void
urcrypt_ed_sign(const uint8_t *message,
                size_t length,
                const uint8_t seed[32],
                uint8_t out[64])
{
  uint8_t public[64], secret[64];

  memset(public, 0, 64);
  memset(secret, 0, 64);
  memset(out, 0, 64);

  ed25519_create_keypair(public, secret, seed);
  ed25519_sign(out, message, length, public, secret);
}

void
urcrypt_ed_add_scalar_private(const uint8_t private[64], const uint8_t scalar[32], uint8_t out[64])
{
  memcpy(out, private, 64);
  ed25519_add_scalar((unsigned char *) 0, out, scalar);
}

void
urcrypt_ed_add_scalar_public(const uint8_t public[32], const uint8_t scalar[32], uint8_t out[32])
{
  memcpy(out, public, 32);
  ed25519_add_scalar(out, (unsigned char *) 0, scalar);
}

void
urcrypt_ed_add_scalar_public_private(const uint8_t public[32],
                           const uint8_t private[64],
                           const uint8_t scalar[32],
                           uint8_t public_out[32],
                           uint8_t private_out[64])
{
  memcpy(public_out, public, 32);
  memcpy(private_out, private, 32);
  ed25519_add_scalar(public_out, private_out, scalar);
}

bool
urcrypt_ed_veri(const uint8_t *message,
                size_t length,
                const uint8_t public[32],
                const uint8_t signature[64])
{
  return ( ed25519_verify(signature, message, length, public) == 1 )
    ? true
    : false;
}


