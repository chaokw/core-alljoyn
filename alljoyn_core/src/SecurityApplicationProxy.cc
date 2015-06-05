/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/SecurityApplicationProxy.h>
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/KeyInfoECC.h>
#include "PermissionMgmtObj.h"
#include "KeyInfoHelper.h"

#define QCC_MODULE "ALLJOYN_SECURITY"

namespace ajn {
SecurityApplicationProxy::SecurityApplicationProxy(BusAttachment& bus, const char* busName, SessionId sessionId) :
    ProxyBusObject(bus, busName, org::alljoyn::Bus::Security::ObjectPath, sessionId)
{
    QStatus status = ER_OK;
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    {
        /* Add org.alljoyn.Bus.Security.Application interface */
        const InterfaceDescription* intf = bus.GetInterface(org::alljoyn::Bus::Security::Application::InterfaceName);
        assert(intf);
        status = AddInterface(*intf);
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to add the %s interface to the %s", org::alljoyn::Bus::Security::Application::InterfaceName, __FUNCTION__));
        }
    }
    {
        /* Add org.alljoyn.Bus.Security.ClaimableApplication interface */
        const InterfaceDescription* intf = bus.GetInterface(org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName);
        assert(intf);
        status = AddInterface(*intf);
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to add the %s interface to the %s", org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName, __FUNCTION__));
        }
    }
    {
        /* Add org.alljoyn.Bus.Security.ManagedApplication interface */
        const InterfaceDescription* intf = bus.GetInterface(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName);
        assert(intf);
        status = AddInterface(*intf);
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to add the %s interface to the %s", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, __FUNCTION__));
        }
    }
}

SecurityApplicationProxy::~SecurityApplicationProxy()
{
}

QStatus SecurityApplicationProxy::GetSecurityApplicationVersion(uint16_t& version)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "Version", arg);
    if (ER_OK == status) {
        version = arg.v_variant.val->v_int16;
    }

    return status;
}

QStatus SecurityApplicationProxy::GetApplicationState(ApplicationState& applicationState)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ApplicationState", arg);
    if (ER_OK == status) {
        applicationState = static_cast<ApplicationState>(arg.v_variant.val->v_int16);
    }

    return status;
}

QStatus SecurityApplicationProxy::GetManifestTemplateDigest(MsgArg& digest)
{
    QCC_UNUSED(digest); //TODO remove on implementation
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ManifestTemplateDigest", arg);
    if (ER_OK == status) {
        //TODO pull the digest from the MsgArg;
    }

    return status;
}

QStatus SecurityApplicationProxy::GetEccPublicKey(qcc::ECCPublicKey& eccPublicKey)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));

    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "EccPublicKey", arg);
    if (ER_OK == status) {
        qcc::KeyInfoNISTP256 keyInfo;
        status = KeyInfoHelper::MsgArgToKeyInfoNISTP256PubKey(arg, keyInfo);
        if (ER_OK == status) {
            eccPublicKey = *keyInfo.GetPublicKey();
        }
    }

    return status;
}

QStatus SecurityApplicationProxy::GetManufacturerCertificate(MsgArg& certificate)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ManufacturerCertificate", arg);
    if (ER_OK == status) {
        certificate = arg;
        certificate.Stabilize();
    }

    return status;
}

QStatus SecurityApplicationProxy::GetManifestTemplate(MsgArg& rules)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ManifestTemplate", arg);
    if (ER_OK == status) {
        rules = arg;
        rules.Stabilize();
    }

    return status;
}

QStatus SecurityApplicationProxy::GetClaimCapabilities(ClaimCapabilities& claimCapabilities)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ClaimCapabilities", arg);
    if (ER_OK == status) {
        claimCapabilities = static_cast<ClaimCapabilities>(arg.v_variant.val->v_int16);
    }

    return status;
}

QStatus SecurityApplicationProxy::GetClaimCapabilityAdditionalInfo(uint16_t& claimCapabilitiesAdditionalInfo)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::Application::InterfaceName, "ClaimCapabilityAdditionalInfo", arg);
    if (ER_OK == status) {
        claimCapabilitiesAdditionalInfo = static_cast<ClaimCapabilityAdditionalInfo>(arg.v_variant.val->v_int16);
    }

    return status;
}

QStatus SecurityApplicationProxy::Claim(const qcc::KeyInfoNISTP256& certificateAuthority,
                                        const qcc::GUID128& adminGroupId,
                                        const qcc::KeyInfoNISTP256& adminGroup,
                                        const qcc::IdentityCertificate* identityCertChain, size_t identityCertChainSize,
                                        const PermissionPolicy::Rule* manifest, size_t manifestSize)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    Message reply(*bus);

    if ((identityCertChain == NULL) || (manifest == NULL)) {
        return ER_INVALID_DATA;
    }
    MsgArg inputs[7];
    qcc::KeyInfoNISTP256 caKeyInfo(certificateAuthority);
    if (caKeyInfo.GetKeyIdLen() == 0) {
        KeyInfoHelper::GenerateKeyId(caKeyInfo);
    }
    KeyInfoHelper::KeyInfoNISTP256PubKeyToMsgArg(caKeyInfo, inputs[0]);
    KeyInfoHelper::KeyInfoKeyIdToMsgArg(caKeyInfo, inputs[1]);

    status = inputs[2].Set("ay", qcc::GUID128::SIZE, adminGroupId.GetBytes());
    if (ER_OK != status) {
        return status;
    }
    qcc::KeyInfoNISTP256 adminGroupKeyInfo(adminGroup);
    if (adminGroupKeyInfo.GetKeyIdLen() == 0) {
        KeyInfoHelper::GenerateKeyId(adminGroupKeyInfo);
    }
    KeyInfoHelper::KeyInfoNISTP256PubKeyToMsgArg(adminGroupKeyInfo, inputs[3]);
    KeyInfoHelper::KeyInfoKeyIdToMsgArg(adminGroupKeyInfo, inputs[4]);

    MsgArg* identityArgs = NULL;
    if (identityCertChainSize == 0) {
        status = inputs[5].Set("a(yay)", 0, NULL);
        if (ER_OK != status) {
            return status;
        }
    } else {
        identityArgs = new MsgArg[identityCertChainSize];
        for (size_t cnt = 0; cnt < identityCertChainSize; cnt++) {
            qcc::String der;
            status = identityCertChain[cnt].EncodeCertificateDER(der);
            if (ER_OK != status) {
                return status;
            }
            status = identityArgs[cnt].Set("(yay)", qcc::CertificateX509::ENCODING_X509_DER, der.size(), der.data());
            if (ER_OK != status) {
                return status;
            }
            identityArgs[cnt].Stabilize();
        }
        status = inputs[5].Set("a(yay)", identityCertChainSize, identityArgs);
        if (ER_OK != status) {
            return status;
        }
    }
    if (manifestSize == 0) {
        status = inputs[6].Set("a(ssa(syy))", 0, NULL);
        if (ER_OK != status) {
            return status;
        }
    } else {
        status = PermissionPolicy::GenerateRules(manifest, manifestSize, inputs[6]);
        if (ER_OK != status) {
            return status;
        }
    }

    status = MethodCall(org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName, "Claim", inputs, 7, reply);
    delete [] identityArgs;
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_PERMISSION_DENIED) == 0) {
                status = ER_PERMISSION_DENIED;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_INVALID_CERTIFICATE) == 0) {
                status = ER_INVALID_CERTIFICATE;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_INVALID_CERTIFICATE_USAGE) == 0) {
                status = ER_INVALID_CERTIFICATE_USAGE;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_DIGEST_MISMATCH) == 0) {
                status = ER_DIGEST_MISMATCH;
            } else if (strcmp(reply->GetErrorName(), org::alljoyn::Bus::ErrorName) == 0 && reply->GetArg(1)) {
                status = static_cast<QStatus>(reply->GetArg(1)->v_uint16);
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
    }
    return status;
}

QStatus SecurityApplicationProxy::GetClaimableApplicationVersion(uint16_t& version)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName, "Version", arg);
    if (ER_OK == status) {
        version = arg.v_variant.val->v_int16;
    }
    return status;
}

QStatus SecurityApplicationProxy::Reset()
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;
    Message reply(*bus);

    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "Reset", NULL, 0, reply);
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_PERMISSION_DENIED) == 0) {
                status = ER_PERMISSION_DENIED;
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
        return status;
    }
    return status;
}

QStatus SecurityApplicationProxy::UpdateIdentity(const qcc::IdentityCertificate* identityCertificateChain, size_t identityCertificateChainSize,
                                                 const PermissionPolicy::Rule* manifest, size_t manifestSize)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));

    if ((identityCertificateChain == NULL) || (identityCertificateChainSize == 0) || (manifest == NULL) || (manifestSize == 0)) {
        return ER_INVALID_DATA;
    }
    QStatus status = ER_OK;
    Message reply(*bus);
    MsgArg inputs[2];
    MsgArg* certArgs = new MsgArg[identityCertificateChainSize];
    for (size_t cnt = 0; cnt < identityCertificateChainSize; cnt++) {
        qcc::String der;
        status = identityCertificateChain[cnt].EncodeCertificateDER(der);
        if (ER_OK != status) {
            return status;
        }
        status = certArgs[cnt].Set("(yay)", qcc::CertificateX509::ENCODING_X509_DER, der.size(), der.data());
        if (ER_OK != status) {
            goto Exit;
        }
        certArgs[cnt].Stabilize();
    }
    status = inputs[0].Set("a(yay)", identityCertificateChainSize, certArgs);
    if (ER_OK != status) {
        goto Exit;
    }
    status = PermissionPolicy::GenerateRules(manifest, manifestSize, inputs[1]);
    if (ER_OK != status) {
        goto Exit;
    }
    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "UpdateIdentity", inputs, 2, reply);

    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_PERMISSION_DENIED) == 0) {
                status = ER_PERMISSION_DENIED;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_INVALID_CERTIFICATE) == 0) {
                status = ER_INVALID_CERTIFICATE;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_INVALID_CERTIFICATE_USAGE) == 0) {
                status = ER_INVALID_CERTIFICATE_USAGE;
            } else if (strcmp(reply->GetErrorName(), PermissionMgmtObj::ERROR_DIGEST_MISMATCH) == 0) {
                status = ER_DIGEST_MISMATCH;
            } else if (strcmp(reply->GetErrorName(), org::alljoyn::Bus::ErrorName) == 0 && reply->GetArg(1)) {
                status = static_cast<QStatus>(reply->GetArg(1)->v_uint16);
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
    }

Exit:
    delete [] certArgs;
    return status;
}

QStatus SecurityApplicationProxy::UpdatePolicy(const PermissionPolicy& policy)
{
    QCC_UNUSED(policy); //TODO remove on implementation
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;
    Message reply(*bus);

    MsgArg inputs[1];
    //TODO convert input params to MsgArgs

    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "UpdatePolicy", inputs, 1, reply);
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.PermissionDenied") == 0) {
                status = ER_PERMISSION_DENIED;
            } else if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.PolicyNotNewer") == 0) {
                //status = ER_POLICY_NOT_NEWER;
                status = ER_NOT_IMPLEMENTED;  //TODO add ER_POLICY_NOT_NEWER to status and delete this status
            } else if (strcmp(reply->GetErrorName(), org::alljoyn::Bus::ErrorName) == 0 && reply->GetArg(1)) {
                status = static_cast<QStatus>(reply->GetArg(1)->v_uint16);
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
        return status;
    }
    return status;
}

QStatus SecurityApplicationProxy::ResetPolicy()
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;
    Message reply(*bus);

    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "ResetPolicy", NULL, 0, reply);
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.PermissionDenied") == 0) {
                status = ER_PERMISSION_DENIED;
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
        return status;
    }
    return status;
}

QStatus SecurityApplicationProxy::InstallMembership(const qcc::CertificateX509* certificateChain, size_t certificateChainSize)
{
    QCC_UNUSED(certificateChain); //TODO remove on implementation
    QCC_UNUSED(certificateChainSize); //TODO remove on implementation
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;
    Message reply(*bus);

    MsgArg inputs[2];
    //TODO convert input params to MsgArgs

    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "InstallMembership", inputs, 2, reply);
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.PermissionDenied") == 0) {
                status = ER_PERMISSION_DENIED;
            } else if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.DuplicateCertificate") == 0) {
                //status = ER_DUPLICATE_CERTIFICATE;
                status = ER_NOT_IMPLEMENTED;  //TODO add ER_DUPLICATE_CERTIFICATE to status and delete this status
            } else if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.InvalidCertificate") == 0) {
                status = ER_DIGEST_MISMATCH;
            } else if (strcmp(reply->GetErrorName(), org::alljoyn::Bus::ErrorName) == 0 && reply->GetArg(1)) {
                status = static_cast<QStatus>(reply->GetArg(1)->v_uint16);
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
        return status;
    }

    return status;
}

QStatus SecurityApplicationProxy::RemoveMembership(const qcc::IdentityCertificate& certificateId)
{
    QCC_UNUSED(certificateId); //TODO remove upon implementation
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;
    Message reply(*bus);

    MsgArg inputs[1];
    //TODO convert input params to MsgArgs

    status = MethodCall(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "RemoveMembership", inputs, 1, reply);
    if (ER_OK != status) {
        if (reply->GetErrorName() != NULL) {
            if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.PermissionDenied") == 0) {
                status = ER_PERMISSION_DENIED;
            } else if (strcmp(reply->GetErrorName(), "org.alljoyn.Bus.Error.CertificateNotFound") == 0) {
                status = ER_CERTIFICATE_NOT_FOUND;
            } else if (strcmp(reply->GetErrorName(), org::alljoyn::Bus::ErrorName) == 0 && reply->GetArg(1)) {
                status = static_cast<QStatus>(reply->GetArg(1)->v_uint16);
            } else {
                QCC_LogError(status, ("SecurityApplicationProxy::%s error %s", __FUNCTION__, reply->GetErrorDescription().c_str()));
            }
        }
        return status;
    }
    return status;
}

QStatus SecurityApplicationProxy::GetManagedApplicationVersion(uint16_t& version)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "Version", arg);
    if (ER_OK == status) {
        version = arg.v_variant.val->v_int16;
    }

    return status;
}

QStatus SecurityApplicationProxy::MsgArgToIdentityCertChain(const MsgArg& arg, qcc::IdentityCertificate* certs, size_t expectedSize)
{
    size_t certChainSize = 0;
    MsgArg* certArgs;
    QStatus status = arg.Get("a(yay)", &certChainSize, &certArgs);
    if (ER_OK != status) {
        return status;
    }
    if (certChainSize != expectedSize) {
        return ER_BAD_ARG_3;
    }

    for (size_t cnt = 0; cnt < certChainSize; cnt++) {
        uint8_t encoding;
        uint8_t* encoded;
        size_t encodedLen;
        status = certArgs[cnt].Get("(yay)", &encoding, &encodedLen, &encoded);
        if (ER_OK == status) {
            status = ER_NOT_IMPLEMENTED;
            if (encoding == qcc::CertificateX509::ENCODING_X509_DER) {
                status = certs[cnt].DecodeCertificateDER(qcc::String((const char*) encoded, encodedLen));
            } else if (encoding == qcc::CertificateX509::ENCODING_X509_DER_PEM) {
                status = certs[cnt].DecodeCertificatePEM(qcc::String((const char*) encoded, encodedLen));
            }
            if (ER_OK != status) {
                return status;
            }
        }
    }
    return status;
}

QStatus SecurityApplicationProxy::GetIdentity(MsgArg& identityCertificate)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "Identity", arg);
    if (ER_OK == status) {
        /* GetProperty returns a variant wrapper */
        MsgArg* resultArg;
        status = arg.Get("v", &resultArg);
        identityCertificate = *resultArg;
        identityCertificate.Stabilize();
    }

    return status;
}

QStatus SecurityApplicationProxy::GetManifest(MsgArg& manifest)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "Manifest", arg);
    if (ER_OK == status) {
        /* GetProperty returns a variant wrapper */
        MsgArg* resultArg;
        status = arg.Get("v", &resultArg);
        if (ER_OK != status) {
            return status;
        }
        manifest = *resultArg;
        manifest.Stabilize();
    }

    return status;
}

QStatus SecurityApplicationProxy::GetIdentityCertificateId(qcc::String& serial, qcc::KeyInfoNISTP256& issuerKeyInfo)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "IdentityCertificateId", arg);
    if (ER_OK == status) {
        /* GetProperty returns a variant wrapper */
        MsgArg* resultArg;
        status = arg.Get("v", &resultArg);
        if (ER_OK != status) {
            return status;
        }
        uint8_t* serialVal;
        size_t serialLen;
        uint8_t* akiVal;
        size_t akiLen;
        uint8_t algorithm;
        uint8_t curve;
        uint8_t* xCoord;
        size_t xLen;
        uint8_t* yCoord;
        size_t yLen;
        status = resultArg->Get("(ayay(yyayay))", &serialLen, &serialVal, &akiLen, &akiVal, &algorithm, &curve, &xLen, &xCoord, &yLen, &yCoord);
        if (ER_OK != status) {
            return ER_INVALID_DATA;
        }
        if (algorithm != qcc::SigInfo::ALGORITHM_ECDSA_SHA_256) {
            return ER_INVALID_DATA;
        }
        if (curve != qcc::Crypto_ECC::ECC_NIST_P256) {
            return ER_INVALID_DATA;
        }
        if ((xLen != qcc::ECC_COORDINATE_SZ) || (yLen != qcc::ECC_COORDINATE_SZ)) {
            return ER_INVALID_DATA;
        }
        issuerKeyInfo.SetXCoord(xCoord);
        issuerKeyInfo.SetYCoord(yCoord);
        issuerKeyInfo.SetKeyId(akiVal, akiLen);
        serial.assign((const char*) serialVal, serialLen);
    }

    return status;
}

QStatus SecurityApplicationProxy::GetPolicyVersion(uint32_t& policyVersion)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "PolicyVersion", arg);
    if (ER_OK == status) {
        policyVersion = arg.v_variant.val->v_uint32;
    }

    return status;
}

QStatus SecurityApplicationProxy::GetPolicy(PermissionPolicy& policy)
{
    QCC_UNUSED(policy); //TODO remove on implementation
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "Policy", arg);
    if (ER_OK == status) {
        //TODO pull the PermissionPolicy from the MsgArg
    }

    return status;
}

QStatus SecurityApplicationProxy::GetDefaultPolicy(PermissionPolicy& defaultPolicy)
{
    QCC_UNUSED(defaultPolicy);
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "DefaultPolicy", arg);
    if (ER_OK == status) {
        //TODO pull the PermissionPolicy from the MsgArg
    }

    return status;
}

QStatus SecurityApplicationProxy::GetMembershipSummaries(MsgArg& membershipSummaries)
{
    QCC_DbgTrace(("SecurityApplicationProxy::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, "MembershipSummaries", arg);
    if (ER_OK == status) {
        membershipSummaries = arg;
        membershipSummaries.Stabilize();
    }

    return status;
}

} // end namespace ajn