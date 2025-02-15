#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "esp32-nodejs"

const char AWS_IOT_ENDPOINT[] = "a2lun2l5vhjcdk-ats.iot.ap-southeast-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAKvd0VjcdbT948EMQ5fBPLiruaCIMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDExMTIwNTIy
NDVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCsxQgcKdC7ksqcpOtV
DzQSP0qr35uihQ98f2+jwEt+00YYPL4NfYzLpXc879CxBi4BoZ4C6N7o5CNI6E8j
R6a2aRCaOSBNjjpwi4u4iQ9SIOTPk7UUAROFWA0uvH/wKF70wU1w5mzK0+P000Q9
V4aTG/lY+iJD73az63uM2dfNpyB/rGVcFXjH0b/F3+8z1bEjcaT+iRfbwEEYVXEN
pN9Tjlo5c3dZ0rZ1byTq20NbSJCjHtxPKbnTbr7EsWguFcvCydgtypMM9sHFN9mb
Rskub7hotZ5kKJ/1XlnVpF23EJ23+xaGSnOOswDUfNwWEo1peCkh7gpdIDbTx0rR
zxhNAgMBAAGjYDBeMB8GA1UdIwQYMBaAFP1+/bELkKmETGTK4D5N77/Nxdk1MB0G
A1UdDgQWBBTq8e7s+il1uc18vsW0oWZ9L5TrqTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAcGUYWtiQSRePHsvF9+/f0E+I
JZE91sGOsF4QGlwXSSDfwdSPy5T+v2B3/xBNzi7oP4DV9oF7j9Y3rO0HbU1cBw6d
Dl4roLvuSEHNn8i4wKHr4zyP9iH961tF83Qs41RNOtWgJRYzDBfzV5bRrO4LHaXy
EqEzsJXCOwZy2CpIUe5CmLy+pxf5Zlw19leKxGFioTliq6owd9rD7ndMF40DtKCg
PZGz5nNAZAYrq7wBXZaXFagINH0mZbu6v+UWHKSBd648oTP8vnr7Wx26M6OmHlzQ
MnlY33IM/fmkbYZ4Yh0Bn/R6KwTh3VNFh6YNIT42krNtM8UV/AOUeNW+BTez9g==
-----END CERTIFICATE-----
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEArMUIHCnQu5LKnKTrVQ80Ej9Kq9+booUPfH9vo8BLftNGGDy+
DX2My6V3PO/QsQYuAaGeAuje6OQjSOhPI0emtmkQmjkgTY46cIuLuIkPUiDkz5O1
FAEThVgNLrx/8Che9MFNcOZsytPj9NNEPVeGkxv5WPoiQ+92s+t7jNnXzacgf6xl
XBV4x9G/xd/vM9WxI3Gk/okX28BBGFVxDaTfU45aOXN3WdK2dW8k6ttDW0iQox7c
Tym5026+xLFoLhXLwsnYLcqTDPbBxTfZm0bJLm+4aLWeZCif9V5Z1aRdtxCdt/sW
hkpzjrMA1HzcFhKNaXgpIe4KXSA208dK0c8YTQIDAQABAoIBACxP6NGYZAIIF1Fv
9y/800Uu2I8WrgtUB3HOGastQe/Ibnz+71v0bK06xkdp1uPgiuI+OpHSeoHPKcGk
W8/Xq8mzTt/PcRqTNSfykqaE+Nn+t9EJuHLmB8S2ncLz8/h70kcCYUNoxlSLXjdI
DIOTNF/818pbdXhpLc/dwPWSVghXvkBdDEkVVS4Od76iPv7aNEG8AMW2Qj6lKX5L
1uzDRQA8Or87johcJPveQoibu58ZUF1ABeKZlb2taeBXmnvPUpQdmJaGnkcitF0v
qyV65kOK5IAvai71COxZE94Tjotv062pgZOV1XlN0KJuI7CfcepCGUqcoSmhASEd
53teneECgYEA29j0nEx0xSvqvoYbtBma31DsRp/led11MyltKTxe3q5+4UiaMzPi
ouWJngDarK9Wh9IgDi1ipcdM2wHU4qwbwge+7W/PErMwQ42WCloecFK01gOB2oK+
LM0Cq9z3BnHVToI4UnSD0HcIPI9bDLWVq/+p4pIWTJ5hZ3q6+/pmlBUCgYEAyS42
zvP52ofhX3HXuxflg9x6Nm0H7BQkVntOm2uv0t8BwCI8GMoylI85BtEsZs55AqPB
q5DTwnjLrgifWHOGxZ2doabcONmR7Up4k7vRndP12qB6eN4P2UilRHDZnr6ftBIH
T+yvTc1+LKMWyCGOP+tpjTuy08dktpzSHtkFaVkCgYEAiUdJPwvy4mgQ9hVR2T0f
2xBx6YvQxC8IDwFwO46KAuzdJ5mpSA2/GE7ShworgicelkMcZx3p+nCfyiWzpDMq
RheGHkdx+1BO8+/GYAJz/Vl3uCeKf0Kis+D0KRMaYTjVpGdl+f7tjE+3ofE2PpJo
unUzxNnJ+N/xHKejeNKcGR0CgYBhngMKOGgsGXLKFTtQlS/Q49KJRi5p5vwa2oox
7/bIo1z+FZ6DiNkyLKzHGggpelZNaZg333ZhDqwGLjjjemsSyIAMSCLjku6z7UbE
qIX1xzusceH7dATMses/YmK2HFjxzy2tInONlQB8OEZ9pYqYiWoWFbmX+VBtK3rp
bPSrQQKBgQCSV55SMLuhPfgqZfk14yr4P+XjxeZ3XnedRjD5gldUV77hazBeSWn4
xHPa0wKH7thedJ6jg+hj2m6HnojtZqCta7wQFjslSGrKk2JlO0u/RikhbbZGIkNh
mbutgHAgFOLQ4U7fAhzeOE0xZ4haKDWuQ5L9aGPDtcQ+mj95a7IP8g==
-----END RSA PRIVATE KEY-----
)KEY";