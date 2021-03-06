#ifndef _ALLJOYN_POLICIES_XML_VALIDATOR_H
#define _ALLJOYN_POLICIES_XML_VALIDATOR_H
/**
 * @file
 * This file defines the validator for Security 2.0 policies in XML format
 */

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

#ifndef __cplusplus
#error Only include XmlPoliciesValidator.h in C++ code.
#endif

#include <qcc/platform.h>
#include <qcc/XmlElement.h>
#include <alljoyn/Status.h>
#include <alljoyn/PermissionPolicy.h>
#include <unordered_set>
#include <unordered_map>
#include <regex>
#include "XmlRulesValidator.h"
#include "XmlValidator.h"

namespace ajn {

#define POLICIES_ROOT_ELEMENT_CHILDREN_COUNT 3
#define ACL_ELEMENT_WITH_RULES_CHILDREN_COUNT 2
#define ACL_ELEMENT_WITHOUT_RULES_CHILDREN_COUNT (ACL_ELEMENT_WITH_RULES_CHILDREN_COUNT - 1)
#define PEER_ALL_ANY_TRUSTED_ELEMENTS_COUNT 1
#define PEER_WITH_PUBLIC_KEY_FROM_CA_ELEMENTS_COUNT 2
#define PEER_WITH_MEMBERSHIP_ELEMENTS_COUNT 3
#define DECIMAL_BASE 10
#define POLICY_VERSION_INDEX 0
#define SERIAL_NUMBER_INDEX 1
#define ACLS_INDEX 2
#define PEERS_INDEX 0
#define RULES_INDEX 1
#define PEER_TYPE_INDEX 0
#define PEER_PUBLIC_KEY_INDEX 1
#define PEER_SGID_INDEX 2
#define VALID_VERSION_NUMBER 1

#define POLICY_XML_ELEMENT "policy"
#define POLICY_VERSION_XML_ELEMENT "policyVersion"
#define SERIAL_NUMBER_XML_ELEMENT "serialNumber"
#define ACLS_XML_ELEMENT "acls"
#define ACL_XML_ELEMENT "acl"
#define PEERS_XML_ELEMENT "peers"
#define PEER_XML_ELEMENT "peer"
#define TYPE_XML_ELEMENT "type"
#define PUBLIC_KEY_XML_ELEMENT "publicKey"
#define SGID_KEY_XML_ELEMENT "sgID"
#define WILDCARD_XML_VALUE "*"

#define XML_PEER_ALL "ALL"
#define XML_PEER_ANY_TRUSTED "ANY_TRUSTED"
#define XML_PEER_FROM_CERTIFICATE_AUTHORITY "FROM_CERTIFICATE_AUTHORITY"
#define XML_PEER_WITH_PUBLIC_KEY "WITH_PUBLIC_KEY"
#define XML_PEER_WITH_MEMBERSHIP "WITH_MEMBERSHIP"

class XmlPoliciesValidator : public XmlValidator {
  public:

    /**
     * Mapping between the peer types in string format and PermissionPolicy::Peer::PeerType enum.
     */
    static std::unordered_map<std::string, PermissionPolicy::Peer::PeerType> s_peerTypeMap;

    /**
     * Initializes the static members.
     */
    static void Init();

    /**
     * Performs the static members cleanup.
     */
    static void Shutdown();

    /**
     * Verifies the input XML follows the policy XML schema
     * available under alljoyn_core/docs/policy.xsd.
     *
     * @param[in]    policyXml   Policy in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_INVALID_ADDRESS if policyXml is null.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus Validate(const qcc::XmlElement* policyXml);

    /**
     * Validates that the PermissionPolicy object maps to an XML
     * that is valid according to the schema for policy rules XMLs.
     * The schema is available under alljoyn_core/docs/policy.xsd.
     *
     * @param[in]   policy  PermissionPolicy object.
     *
     * @return
     *            #ER_OK if the input is correct.
     *            #ER_FAIL if the policy is not following the schema.
     */
    static QStatus Validate(const PermissionPolicy& policy);

    /**
     * Default destructor.
     */
    virtual ~XmlPoliciesValidator() { }

  private:

    /*
     * Factory building validators for "peer" elements depending on their type.
     */
    class PeerValidatorFactory;

    /**
     * Verifies the "policyVersion" XML element follows the policy XML schema.
     *
     * @param[in]    policyVersion   Policy version in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidatePolicyVersion(const qcc::XmlElement* policyVersion);

    /**
     * Verifies the contents of the "policyVersion" XML element follow the policy XML schema.
     *
     * @param[in]    policyVersion   Policy version in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidatePolicyVersionContent(const qcc::XmlElement* policyVersion);

    /**
     * Verifies the "serialNumber" XML element follows the policy XML schema.
     *
     * @param[in]    serialNumber   Policy version in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidateSerialNumber(const qcc::XmlElement* serialNumber);

    /**
     * Veifies if the contents of the "serialNumber" XML element follow the policy XML schema.
     *
     * @param[in]    serialNumber   Policy version in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidateSerialNumberContent(const qcc::XmlElement* policySerialNumber);

    /**
     * Veifies if the "acls" XML element follows the policy XML schema.
     *
     * @param[in]    acls   ACLs in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidateAcls(const qcc::XmlElement* acls);

    /**
     * Veifies if the "acl" XML element follows the policy XML schema.
     *
     * @param[in]    acl   Single ACL in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidateAcl(const qcc::XmlElement* acl);

    /**
     * Veifies if the "peers" XML element follows the policy XML schema.
     *
     * @param[in]    peers   Permission policy peers in XML format.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidatePeers(const qcc::XmlElement* peers);

    /**
     * Veifies if the "peer" XML element follows the policy XML schema.
     *
     * @param[in]    peer                    Single permission policy peer in XML format.
     * @param[in]    peerValidatorFactory    Factory building peer validators depending on the peer type.
     *
     * @return   #ER_OK if XML is valid.
     *           #ER_XML_MALFORMED if the XML does not follow the policy XML schema.
     */
    static QStatus ValidatePeer(const qcc::XmlElement* peer, PeerValidatorFactory& peerValidatorFactory);

    /**
     * Verifies the policy version.
     *
     * @param[in]    policyVersion   Policy version.
     *
     * @return   #ER_OK      If the policy version is valid.
     *           #ER_FAIL    If the policy version is invalid.
     */
    static QStatus ValidatePolicyVersion(uint32_t policyVersion);

    /**
     * Veifies if the policy's ACLs are valid.
     *
     * @param[in]    acls        An array of policy's ACLs.
     * @param[in]    aclsSize    Count of policy's ACLs.
     *
     * @return   #ER_OK      If the policy's ACLs are valid.
     *           #ER_FAIL    If the policy's ACLs are invalid.
     */
    static QStatus ValidateAcls(const PermissionPolicy::Acl* acls, size_t aclsSize);

    /**
     * Veifies if a single policy's ACL is valid.
     *
     * @param[in]    acl   Single policy's ACL.
     *
     * @return   #ER_OK      If the policy's ACL is valid.
     *           #ER_FAIL    If the policy's ACL is invalid.
     */
    static QStatus ValidateAcl(const PermissionPolicy::Acl& acl);

    /**
     * Veifies if the policy's peers are valid.
     *
     * @param[in]    peers       An array of permission policy peers.
     * @param[in]    peersSize   Count of policy's peers.
     *
     * @return   #ER_OK      If the policy's peers are valid.
     *           #ER_FAIL    If the policy's peers are invalid.
     */
    static QStatus ValidatePeers(const PermissionPolicy::Peer* peers, size_t peersSize);


    /*
     * Base class for validating XML "peer" elements.
     */
    class PeerValidator {
      public:

        /**
         * Constructor.
         */
        PeerValidator() :
            m_allTypeAbsent(true),
            m_firstPeer(true),
            m_anyTrustedTypePresent(false)
        { }

        /**
         * Default destructor.
         */
        virtual ~PeerValidator()
        { }

        /**
         * Validates the peer given as qcc::XmlElement object.
         *
         * @param[in]    peer  Validated peer.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED otherwise.
         */
        virtual QStatus Validate(const qcc::XmlElement* peer);

        /**
         * Validates the peer given as an PermissionPolicy::Peer object.
         *
         * @param[in]    peer  Validated peer.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_FAIL otherwise.
         */
        virtual QStatus Validate(const PermissionPolicy::Peer& peer);

        /**
         */
        void UpdatePeersFlags(bool allTypeAbsent, bool firstPeer, bool anyTrustedTypePresent);

        /**
         * Returns a peer type from the qcc::XmlElement or an error if
         * the XML element didn't contain the correct information.
         *
         * @param[in]    peer        A XML "peer" element.
         * @param[out]   peerType    Retrieved peer type.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        static QStatus GetValidPeerType(const qcc::XmlElement* peer, PermissionPolicy::Peer::PeerType* peerType);

      protected:

        /**
         * Flag indicating that previously checked peer was not an "ALL" type.
         */
        bool m_allTypeAbsent;

        /**
         * Flag indicating that this is the first checked peer element.
         */
        bool m_firstPeer;

        /**
         * Flag indicating that an "ANY_TRUSTED" peer has already been validated.
         */
        bool m_anyTrustedTypePresent;

        /**
         * Validates peer details specific to a given type.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        virtual QStatus ValidateTypeSpecific(const qcc::XmlElement* peer);

        /**
         * Validates peer details specific to a given type.
         *
         * @param[in]    peer    The validated peer.
         *
         * @return  #ER_OK   If the input is correct.
         *          #ER_FAIL If the peer is not valid.
         */
        virtual QStatus ValidateTypeSpecific(const PermissionPolicy::Peer& peer) = 0;

        /**
         * Retrieves the expected children count of the validated peer element.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        virtual size_t GetPeerChildrenCount() = 0;

      private:

        /**
         * Performs a check if either the "ALL" type peers is the only one present or
         * is not present at all.
         *
         * @return  #ER_OK if true.
         *          #ER_FAIL otherwise.
         */
        QStatus ValidateAllTypeAbsentOrOnlyPeer();

        /**
         * Validates peer contents that are common for all peer types.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        QStatus ValidateCommon(const qcc::XmlElement* peer);

        /**
         * Validates peer contents that are common for all peer types.
         *
         * @return  #ER_OK      If the input is correct.
         *          #ER_FAIL    If the peer is not valid.
         */
        QStatus ValidateCommon();

        /**
         * Validates if the peer contains the correct number of child eleemnts.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        QStatus ValidateChildrenCount(const qcc::XmlElement* peer);
    };


    class PeerWithoutPublicKey : public PeerValidator {
      protected:

        virtual QStatus ValidateTypeSpecific(const PermissionPolicy::Peer& peer);
    };


    class AllValidator : public PeerWithoutPublicKey {
      private:

        virtual size_t GetPeerChildrenCount();
    };


    class AnyTrustedValidator : public PeerWithoutPublicKey {
      private:

        virtual size_t GetPeerChildrenCount();

        virtual QStatus ValidateTypeSpecific(const qcc::XmlElement* peer);

        virtual QStatus ValidateTypeSpecific(const PermissionPolicy::Peer& peer);
    };


    /*
     * Class for validating peers conataining a "publicKey" XML element.
     */
    class PeerWithPublicKeyValidator : public PeerValidator {
      protected:

        virtual QStatus ValidateTypeSpecific(const qcc::XmlElement* peer);

        virtual QStatus ValidateTypeSpecific(const PermissionPolicy::Peer& peer);

        /**
         * Retrieves the the currently validated peer's ID.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  Current peer's ID. An ID is either the peer's public key
         * or public key and sgID - type dependent.
         */
        virtual std::string GetPeerId(const qcc::XmlElement* peer);

        /**
         * Retrieves the the currently validated peer's ID.
         *
         * @param[in]    peer    The validated peer object.
         *
         * @return  Current peer's ID. An ID is either the peer's public key
         * or public key and sgID - type dependent.
         */
        virtual std::string GetPeerId(const PermissionPolicy::Peer& peer);

      private:

        /**
         * Set of IDs of all previously checked peers of a given type. An ID is either the peer's public key
         * or public key and sgID - type dependent. "ALL" and "ANY_TRUSTED" type peers do not have IDs.
         */
        std::unordered_set<std::string> m_peersIds;

        /**
         * Validates the peer is unique in terms of its type and ID.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        QStatus ValidatePeerUnique(const qcc::XmlElement* peer);

        /**
         * Validates the peer is unique in terms of its type and ID.
         *
         * @param[in]    peer    The validated peer.
         *
         * @return  #ER_OK   If the input is correct.
         *          #ER_FAIL If the peer is not valid.
         */
        QStatus ValidatePeerUnique(const PermissionPolicy::Peer& peer);

        /**
         * Validates the peer's public key is in correct PEM format.
         *
         * @param[in]    peer    A XML "peer" element.
         *
         * @return  #ER_OK if the input is correct.
         *          #ER_XML_MALFORMED if the XML is not a valid peer.
         */
        QStatus ValidatePublicKey(const qcc::XmlElement* peer);

        /**
         * Validates that the peer's public key is set.
         *
         * @param[in]    peer    The validated peer.
         *
         * @return  #ER_OK   If the input is correct.
         *          #ER_FAIL If the peer is not valid.
         */
        QStatus ValidatePublicKey(const PermissionPolicy::Peer& peer);

        virtual size_t GetPeerChildrenCount();
    };


    class WithMembershipValidator : public PeerWithPublicKeyValidator {
      private:

        QStatus ValidateSgId(const qcc::XmlElement* peer);

        virtual QStatus ValidateTypeSpecific(const qcc::XmlElement* peer);

        virtual size_t GetPeerChildrenCount();

        virtual std::string GetPeerId(const qcc::XmlElement* peer);

        virtual std::string GetPeerId(const PermissionPolicy::Peer& peer);
    };

    /*
     * A factory class to return proper PeerValidators according to their type.
     */
    class PeerValidatorFactory {
      public:

        PeerValidatorFactory() :
            m_allTypeAbsent(true),
            m_firstPeer(true),
            m_anyTrustedTypePresent(false)
        {
            m_validators[PermissionPolicy::Peer::PeerType::PEER_ALL] = new AllValidator();
            m_validators[PermissionPolicy::Peer::PeerType::PEER_ANY_TRUSTED] = new AnyTrustedValidator();
            m_validators[PermissionPolicy::Peer::PeerType::PEER_WITH_PUBLIC_KEY] = new PeerWithPublicKeyValidator();
            m_validators[PermissionPolicy::Peer::PeerType::PEER_WITH_MEMBERSHIP] = new WithMembershipValidator();
            m_validators[PermissionPolicy::Peer::PeerType::PEER_FROM_CERTIFICATE_AUTHORITY] = new PeerWithPublicKeyValidator();
        }

        ~PeerValidatorFactory()
        {
            for (auto validatorsElement : m_validators) {
                delete validatorsElement.second;
            }
        }

        /**
         * Constructs a validator for given peer type.
         *
         * @param[in]   type  Peer's type.
         *
         * @return A validator for given peer type.
         */
        PeerValidator* ForType(PermissionPolicy::Peer::PeerType type);

      private:

        /**
         * Flag indicating that previously checked peer was not an "ALL" type.
         */
        bool m_allTypeAbsent;

        /**
         * Flag indicating that this is the first checked peer element.
         */
        bool m_firstPeer;

        /**
         * Flag indicating that an "ANY_TRUSTED" type peer was already present.
         */
        bool m_anyTrustedTypePresent;

        /**
         * Peer validators returned by the factory.
         */
        std::map<PermissionPolicy::Peer::PeerType, PeerValidator*> m_validators;

        /**
         * Updates information about already analyzed peers.
         */
        void UpdatePeersFlags(PermissionPolicy::Peer::PeerType type);
    };
};
} /* namespace ajn */
#endif