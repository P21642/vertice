# include "payment.h"

# include <cstdio>
# include <cstring>
# include <strings.h>
# include <cstdlib>

# define KEY_SIZE 128

 const char *env_key = getenv("PAYMENT_KEY");

/* Simula o gateway de pagamentos, que aceita o pagamento quando a chave foi informada e o valor é positivo. */
static bool gatewayAuthorize(const char *key, double amount)
{
    return key[0] != '\0' && amount > 0.0;
}

/* Autoriza o pagamento com a chave do gateway e apaga a chave da memória logo depois do uso. */
bool processPayment(double amount)
{
    char key[KEY_SIZE];
    bool authorized;

    snprintf(key, sizeof key, "%s", env_key != nullptr ? env_key : "");
    authorized = gatewayAuthorize(key, amount);
    explicit_bzero(key, sizeof key);
    return authorized;
}
