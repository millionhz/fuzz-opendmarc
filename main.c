#include <stdio.h>
#include <stdlib.h>
#include <opendmarc/dmarc.h>
#include <sys/types.h>

typedef unsigned char u_char;

int main(int argc, char *argv[])
{
    // Check for required arguments
    if (argc < 3) // Expecting at least 2 arguments: DMARC record and domain
    {
        fprintf(stderr, "Usage: %s <DMARC record> <domain> [organizational domain]\n", argv[0]);
        return 1;
    }

    // Extract arguments from command line
    const char *dmarc_record = argv[1];
    const char *domain = argv[2];
    const char *organizational_domain = (argc >= 4) ? argv[3] : NULL;

    // Initialize a DMARC policy context
    DMARC_POLICY_T *policy = opendmarc_policy_connect_init("127.0.0.1", 0);
    if (policy == NULL)
    {
        fprintf(stderr, "Error: Failed to initialize DMARC policy context.\n");
        return 1;
    }

    // Store the DMARC record
    OPENDMARC_STATUS_T status = opendmarc_policy_store_dmarc(
        policy,
        (u_char *)dmarc_record,
        (u_char *)domain,
        (u_char *)organizational_domain);

    // Check the status and print the output
    if (status == DMARC_PARSE_OKAY)
    {
        printf("DMARC record stored successfully.\n");
    }
    else
    {
        printf("Error storing DMARC record. Error code: %d\n", status);
        switch (status)
        {
        case DMARC_PARSE_ERROR_NULL_CTX:
            printf("Error: NULL context provided.\n");
            break;
        case DMARC_PARSE_ERROR_EMPTY:
            printf("Error: DMARC record is empty.\n");
            break;
        case DMARC_PARSE_ERROR_NO_DOMAIN:
            printf("Error: No domain provided.\n");
            break;
        case DMARC_PARSE_ERROR_BAD_VERSION:
            printf("Error: Bad DMARC version (v= tag).\n");
            break;
        case DMARC_PARSE_ERROR_BAD_VALUE:
            printf("Error: Bad value in DMARC record.\n");
            break;
        case DMARC_PARSE_ERROR_NO_REQUIRED_P:
            printf("Error: Missing required 'p=' tag.\n");
            break;
        default:
            printf("Unknown error.\n");
            break;
        }
    }

    // Clean up
    opendmarc_policy_connect_shutdown(policy);

    return 0;
}
