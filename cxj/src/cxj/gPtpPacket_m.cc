//
// Generated file, do not edit! Created by nedtool 5.6 from src/cxj/gPtpPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "gPtpPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace cxj {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("cxj::GptpNodeType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("cxj::GptpNodeType"));
    e->insert(MASTER_NODE, "MASTER_NODE");
    e->insert(BRIDGE_NODE, "BRIDGE_NODE");
    e->insert(SLAVE_NODE, "SLAVE_NODE");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("cxj::GptpPortType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("cxj::GptpPortType"));
    e->insert(MASTER_PORT, "MASTER_PORT");
    e->insert(SLAVE_PORT, "SLAVE_PORT");
    e->insert(PASSIVE_PORT, "PASSIVE_PORT");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("cxj::GptpMessageType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("cxj::GptpMessageType"));
    e->insert(GPTPTYPE_SYNC, "GPTPTYPE_SYNC");
    e->insert(GPTPTYPE_FOLLOW_UP, "GPTPTYPE_FOLLOW_UP");
    e->insert(GPTPTYPE_PDELAY_REQ, "GPTPTYPE_PDELAY_REQ");
    e->insert(GPTPTYPE_PDELAY_RESP, "GPTPTYPE_PDELAY_RESP");
    e->insert(GPTPTYPE_PDELAY_RESP_FOLLOW_UP, "GPTPTYPE_PDELAY_RESP_FOLLOW_UP");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("cxj::GptpSelfMsgKind");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("cxj::GptpSelfMsgKind"));
    e->insert(GPTP_SELF_REQ_ANSWER_KIND, "GPTP_SELF_REQ_ANSWER_KIND");
    e->insert(GPTP_SELF_MSG_SYNC, "GPTP_SELF_MSG_SYNC");
    e->insert(GPTP_REQUEST_TO_SEND_SYNC, "GPTP_REQUEST_TO_SEND_SYNC");
    e->insert(GPTP_SELF_MSG_PDELAY_REQ, "GPTP_SELF_MSG_PDELAY_REQ");
)

PortIdentity::PortIdentity()
{
    this->clockIdentity = 0;
    this->portNumber = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const PortIdentity& a)
{
    doParsimPacking(b,a.clockIdentity);
    doParsimPacking(b,a.portNumber);
}

void __doUnpacking(omnetpp::cCommBuffer *b, PortIdentity& a)
{
    doParsimUnpacking(b,a.clockIdentity);
    doParsimUnpacking(b,a.portNumber);
}

class PortIdentityDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PortIdentityDescriptor();
    virtual ~PortIdentityDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PortIdentityDescriptor)

PortIdentityDescriptor::PortIdentityDescriptor() : omnetpp::cClassDescriptor("cxj::PortIdentity", "")
{
    propertynames = nullptr;
}

PortIdentityDescriptor::~PortIdentityDescriptor()
{
    delete[] propertynames;
}

bool PortIdentityDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PortIdentity *>(obj)!=nullptr;
}

const char **PortIdentityDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PortIdentityDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PortIdentityDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int PortIdentityDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *PortIdentityDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clockIdentity",
        "portNumber",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int PortIdentityDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "clockIdentity")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "portNumber")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PortIdentityDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",
        "uint16_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **PortIdentityDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PortIdentityDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PortIdentityDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PortIdentity *pp = (PortIdentity *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PortIdentityDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PortIdentity *pp = (PortIdentity *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PortIdentityDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PortIdentity *pp = (PortIdentity *)object; (void)pp;
    switch (field) {
        case 0: return uint642string(pp->clockIdentity);
        case 1: return ulong2string(pp->portNumber);
        default: return "";
    }
}

bool PortIdentityDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PortIdentity *pp = (PortIdentity *)object; (void)pp;
    switch (field) {
        case 0: pp->clockIdentity = string2uint64(value); return true;
        case 1: pp->portNumber = string2ulong(value); return true;
        default: return false;
    }
}

const char *PortIdentityDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *PortIdentityDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PortIdentity *pp = (PortIdentity *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

GptpBase::GptpBase() : ::inet::FieldsChunk()
{
    this->messageType = 0;
}

GptpBase::GptpBase(const GptpBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

GptpBase::~GptpBase()
{
}

GptpBase& GptpBase::operator=(const GptpBase& other)
{
    if (this==&other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void GptpBase::copy(const GptpBase& other)
{
    this->messageType = other.messageType;
    this->correctionField = other.correctionField;
    this->sourcePortIdentity = other.sourcePortIdentity;
}

void GptpBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::inet::FieldsChunk&)*this);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->correctionField);
    doParsimPacking(b,this->sourcePortIdentity);
}

void GptpBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::inet::FieldsChunk&)*this);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->correctionField);
    doParsimUnpacking(b,this->sourcePortIdentity);
}

int GptpBase::getMessageType() const
{
    return this->messageType;
}

void GptpBase::setMessageType(int messageType)
{
    this->messageType = messageType;
}

omnetpp::simtime_t& GptpBase::getCorrectionField()
{
    return this->correctionField;
}

void GptpBase::setCorrectionField(const omnetpp::simtime_t& correctionField)
{
    this->correctionField = correctionField;
}

PortIdentity& GptpBase::getSourcePortIdentity()
{
    return this->sourcePortIdentity;
}

void GptpBase::setSourcePortIdentity(const PortIdentity& sourcePortIdentity)
{
    this->sourcePortIdentity = sourcePortIdentity;
}

class GptpBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpBaseDescriptor();
    virtual ~GptpBaseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpBaseDescriptor)

GptpBaseDescriptor::GptpBaseDescriptor() : omnetpp::cClassDescriptor("cxj::GptpBase", "inet::FieldsChunk")
{
    propertynames = nullptr;
}

GptpBaseDescriptor::~GptpBaseDescriptor()
{
    delete[] propertynames;
}

bool GptpBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpBase *>(obj)!=nullptr;
}

const char **GptpBaseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpBaseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int GptpBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *GptpBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "messageType",
        "correctionField",
        "sourcePortIdentity",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int GptpBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageType")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "correctionField")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePortIdentity")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "omnetpp::simtime_t",
        "PortIdentity",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *GptpBaseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "cxj::GptpMessageType";
            return nullptr;
        default: return nullptr;
    }
}

int GptpBaseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpBase *pp = (GptpBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpBaseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpBase *pp = (GptpBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpBaseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpBase *pp = (GptpBase *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getMessageType(), "cxj::GptpMessageType");
        case 1: {std::stringstream out; out << pp->getCorrectionField(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSourcePortIdentity(); return out.str();}
        default: return "";
    }
}

bool GptpBaseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpBase *pp = (GptpBase *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageType((cxj::GptpMessageType)string2enum(value, "cxj::GptpMessageType")); return true;
        default: return false;
    }
}

const char *GptpBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        case 2: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

void *GptpBaseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpBase *pp = (GptpBase *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getCorrectionField()); break;
        case 2: return (void *)(&pp->getSourcePortIdentity()); break;
        default: return nullptr;
    }
}

GptpSync::GptpSync() : ::cxj::GptpBase()
{
    this->setMessageType(GPTPTYPE_SYNC);
    this->setChunkLength(GPTP_SYNC_2STEP_PACKET_SIZE);

}

GptpSync::GptpSync(const GptpSync& other) : ::cxj::GptpBase(other)
{
    copy(other);
}

GptpSync::~GptpSync()
{
}

GptpSync& GptpSync::operator=(const GptpSync& other)
{
    if (this==&other) return *this;
    ::cxj::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpSync::copy(const GptpSync& other)
{
    this->originTimestamp = other.originTimestamp;
}

void GptpSync::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::cxj::GptpBase&)*this);
    doParsimPacking(b,this->originTimestamp);
}

void GptpSync::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::cxj::GptpBase&)*this);
    doParsimUnpacking(b,this->originTimestamp);
}

omnetpp::simtime_t& GptpSync::getOriginTimestamp()
{
    return this->originTimestamp;
}

void GptpSync::setOriginTimestamp(const omnetpp::simtime_t& originTimestamp)
{
    this->originTimestamp = originTimestamp;
}

class GptpSyncDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpSyncDescriptor();
    virtual ~GptpSyncDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpSyncDescriptor)

GptpSyncDescriptor::GptpSyncDescriptor() : omnetpp::cClassDescriptor("cxj::GptpSync", "cxj::GptpBase")
{
    propertynames = nullptr;
}

GptpSyncDescriptor::~GptpSyncDescriptor()
{
    delete[] propertynames;
}

bool GptpSyncDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpSync *>(obj)!=nullptr;
}

const char **GptpSyncDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpSyncDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpSyncDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GptpSyncDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GptpSyncDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "originTimestamp",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GptpSyncDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "originTimestamp")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpSyncDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpSyncDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpSyncDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpSyncDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpSync *pp = (GptpSync *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpSyncDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpSync *pp = (GptpSync *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpSyncDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpSync *pp = (GptpSync *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getOriginTimestamp(); return out.str();}
        default: return "";
    }
}

bool GptpSyncDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpSync *pp = (GptpSync *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GptpSyncDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        default: return nullptr;
    };
}

void *GptpSyncDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpSync *pp = (GptpSync *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getOriginTimestamp()); break;
        default: return nullptr;
    }
}

GptpFollowUp::GptpFollowUp() : ::cxj::GptpBase()
{
    this->setMessageType(GPTPTYPE_FOLLOW_UP);
    this->setChunkLength(GPTP_FOLLOW_UP_PACKET_SIZE);

    this->rateRatio = 0;
}

GptpFollowUp::GptpFollowUp(const GptpFollowUp& other) : ::cxj::GptpBase(other)
{
    copy(other);
}

GptpFollowUp::~GptpFollowUp()
{
}

GptpFollowUp& GptpFollowUp::operator=(const GptpFollowUp& other)
{
    if (this==&other) return *this;
    ::cxj::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpFollowUp::copy(const GptpFollowUp& other)
{
    this->preciseOriginTimestamp = other.preciseOriginTimestamp;
    this->rateRatio = other.rateRatio;
}

void GptpFollowUp::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::cxj::GptpBase&)*this);
    doParsimPacking(b,this->preciseOriginTimestamp);
    doParsimPacking(b,this->rateRatio);
}

void GptpFollowUp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::cxj::GptpBase&)*this);
    doParsimUnpacking(b,this->preciseOriginTimestamp);
    doParsimUnpacking(b,this->rateRatio);
}

omnetpp::simtime_t& GptpFollowUp::getPreciseOriginTimestamp()
{
    return this->preciseOriginTimestamp;
}

void GptpFollowUp::setPreciseOriginTimestamp(const omnetpp::simtime_t& preciseOriginTimestamp)
{
    this->preciseOriginTimestamp = preciseOriginTimestamp;
}

double GptpFollowUp::getRateRatio() const
{
    return this->rateRatio;
}

void GptpFollowUp::setRateRatio(double rateRatio)
{
    this->rateRatio = rateRatio;
}

class GptpFollowUpDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpFollowUpDescriptor();
    virtual ~GptpFollowUpDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpFollowUpDescriptor)

GptpFollowUpDescriptor::GptpFollowUpDescriptor() : omnetpp::cClassDescriptor("cxj::GptpFollowUp", "cxj::GptpBase")
{
    propertynames = nullptr;
}

GptpFollowUpDescriptor::~GptpFollowUpDescriptor()
{
    delete[] propertynames;
}

bool GptpFollowUpDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpFollowUp *>(obj)!=nullptr;
}

const char **GptpFollowUpDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpFollowUpDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpFollowUpDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GptpFollowUpDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GptpFollowUpDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "preciseOriginTimestamp",
        "rateRatio",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GptpFollowUpDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "preciseOriginTimestamp")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "rateRatio")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpFollowUpDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpFollowUpDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpFollowUpDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpFollowUpDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpFollowUp *pp = (GptpFollowUp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpFollowUpDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpFollowUp *pp = (GptpFollowUp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpFollowUpDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpFollowUp *pp = (GptpFollowUp *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getPreciseOriginTimestamp(); return out.str();}
        case 1: return double2string(pp->getRateRatio());
        default: return "";
    }
}

bool GptpFollowUpDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpFollowUp *pp = (GptpFollowUp *)object; (void)pp;
    switch (field) {
        case 1: pp->setRateRatio(string2double(value)); return true;
        default: return false;
    }
}

const char *GptpFollowUpDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        default: return nullptr;
    };
}

void *GptpFollowUpDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpFollowUp *pp = (GptpFollowUp *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getPreciseOriginTimestamp()); break;
        default: return nullptr;
    }
}

GptpPdelayReq::GptpPdelayReq() : ::cxj::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_REQ);
    this->setChunkLength(GPTP_PDELAY_REQ_PACKET_SIZE);

}

GptpPdelayReq::GptpPdelayReq(const GptpPdelayReq& other) : ::cxj::GptpBase(other)
{
    copy(other);
}

GptpPdelayReq::~GptpPdelayReq()
{
}

GptpPdelayReq& GptpPdelayReq::operator=(const GptpPdelayReq& other)
{
    if (this==&other) return *this;
    ::cxj::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayReq::copy(const GptpPdelayReq& other)
{
    this->reserved1 = other.reserved1;
    this->reserved2 = other.reserved2;
}

void GptpPdelayReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::cxj::GptpBase&)*this);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->reserved2);
}

void GptpPdelayReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::cxj::GptpBase&)*this);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->reserved2);
}

omnetpp::simtime_t& GptpPdelayReq::getReserved1()
{
    return this->reserved1;
}

void GptpPdelayReq::setReserved1(const omnetpp::simtime_t& reserved1)
{
    this->reserved1 = reserved1;
}

omnetpp::simtime_t& GptpPdelayReq::getReserved2()
{
    return this->reserved2;
}

void GptpPdelayReq::setReserved2(const omnetpp::simtime_t& reserved2)
{
    this->reserved2 = reserved2;
}

class GptpPdelayReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpPdelayReqDescriptor();
    virtual ~GptpPdelayReqDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpPdelayReqDescriptor)

GptpPdelayReqDescriptor::GptpPdelayReqDescriptor() : omnetpp::cClassDescriptor("cxj::GptpPdelayReq", "cxj::GptpBase")
{
    propertynames = nullptr;
}

GptpPdelayReqDescriptor::~GptpPdelayReqDescriptor()
{
    delete[] propertynames;
}

bool GptpPdelayReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayReq *>(obj)!=nullptr;
}

const char **GptpPdelayReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpPdelayReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpPdelayReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GptpPdelayReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "reserved2",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GptpPdelayReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved1")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved2")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpPdelayReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
        "omnetpp::simtime_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayReqDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpPdelayReqDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpPdelayReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayReq *pp = (GptpPdelayReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpPdelayReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayReq *pp = (GptpPdelayReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayReq *pp = (GptpPdelayReq *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getReserved1(); return out.str();}
        case 1: {std::stringstream out; out << pp->getReserved2(); return out.str();}
        default: return "";
    }
}

bool GptpPdelayReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayReq *pp = (GptpPdelayReq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GptpPdelayReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        case 1: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        default: return nullptr;
    };
}

void *GptpPdelayReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayReq *pp = (GptpPdelayReq *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getReserved1()); break;
        case 1: return (void *)(&pp->getReserved2()); break;
        default: return nullptr;
    }
}

GptpPdelayResp::GptpPdelayResp() : ::cxj::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_RESP);
    this->setChunkLength(GPTP_PDELAY_RESP_PACKET_SIZE);

}

GptpPdelayResp::GptpPdelayResp(const GptpPdelayResp& other) : ::cxj::GptpBase(other)
{
    copy(other);
}

GptpPdelayResp::~GptpPdelayResp()
{
}

GptpPdelayResp& GptpPdelayResp::operator=(const GptpPdelayResp& other)
{
    if (this==&other) return *this;
    ::cxj::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayResp::copy(const GptpPdelayResp& other)
{
    this->requestReceiptTimestamp = other.requestReceiptTimestamp;
    this->requestingPortIdentity = other.requestingPortIdentity;
}

void GptpPdelayResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::cxj::GptpBase&)*this);
    doParsimPacking(b,this->requestReceiptTimestamp);
    doParsimPacking(b,this->requestingPortIdentity);
}

void GptpPdelayResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::cxj::GptpBase&)*this);
    doParsimUnpacking(b,this->requestReceiptTimestamp);
    doParsimUnpacking(b,this->requestingPortIdentity);
}

omnetpp::simtime_t& GptpPdelayResp::getRequestReceiptTimestamp()
{
    return this->requestReceiptTimestamp;
}

void GptpPdelayResp::setRequestReceiptTimestamp(const omnetpp::simtime_t& requestReceiptTimestamp)
{
    this->requestReceiptTimestamp = requestReceiptTimestamp;
}

PortIdentity& GptpPdelayResp::getRequestingPortIdentity()
{
    return this->requestingPortIdentity;
}

void GptpPdelayResp::setRequestingPortIdentity(const PortIdentity& requestingPortIdentity)
{
    this->requestingPortIdentity = requestingPortIdentity;
}

class GptpPdelayRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpPdelayRespDescriptor();
    virtual ~GptpPdelayRespDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpPdelayRespDescriptor)

GptpPdelayRespDescriptor::GptpPdelayRespDescriptor() : omnetpp::cClassDescriptor("cxj::GptpPdelayResp", "cxj::GptpBase")
{
    propertynames = nullptr;
}

GptpPdelayRespDescriptor::~GptpPdelayRespDescriptor()
{
    delete[] propertynames;
}

bool GptpPdelayRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayResp *>(obj)!=nullptr;
}

const char **GptpPdelayRespDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpPdelayRespDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpPdelayRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GptpPdelayRespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestReceiptTimestamp",
        "requestingPortIdentity",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GptpPdelayRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requestReceiptTimestamp")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requestingPortIdentity")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpPdelayRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
        "PortIdentity",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayRespDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpPdelayRespDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpPdelayRespDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayResp *pp = (GptpPdelayResp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpPdelayRespDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayResp *pp = (GptpPdelayResp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayRespDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayResp *pp = (GptpPdelayResp *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRequestReceiptTimestamp(); return out.str();}
        case 1: {std::stringstream out; out << pp->getRequestingPortIdentity(); return out.str();}
        default: return "";
    }
}

bool GptpPdelayRespDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayResp *pp = (GptpPdelayResp *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GptpPdelayRespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        case 1: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

void *GptpPdelayRespDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayResp *pp = (GptpPdelayResp *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRequestReceiptTimestamp()); break;
        case 1: return (void *)(&pp->getRequestingPortIdentity()); break;
        default: return nullptr;
    }
}

GptpPdelayRespFollowUp::GptpPdelayRespFollowUp() : ::cxj::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_RESP_FOLLOW_UP);
    this->setChunkLength(GPTP_PDELAY_RESP_FOLLOW_UP_PACKET_SIZE);

}

GptpPdelayRespFollowUp::GptpPdelayRespFollowUp(const GptpPdelayRespFollowUp& other) : ::cxj::GptpBase(other)
{
    copy(other);
}

GptpPdelayRespFollowUp::~GptpPdelayRespFollowUp()
{
}

GptpPdelayRespFollowUp& GptpPdelayRespFollowUp::operator=(const GptpPdelayRespFollowUp& other)
{
    if (this==&other) return *this;
    ::cxj::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayRespFollowUp::copy(const GptpPdelayRespFollowUp& other)
{
    this->responseOriginTimestamp = other.responseOriginTimestamp;
    this->requestingPortIdentity = other.requestingPortIdentity;
}

void GptpPdelayRespFollowUp::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::cxj::GptpBase&)*this);
    doParsimPacking(b,this->responseOriginTimestamp);
    doParsimPacking(b,this->requestingPortIdentity);
}

void GptpPdelayRespFollowUp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::cxj::GptpBase&)*this);
    doParsimUnpacking(b,this->responseOriginTimestamp);
    doParsimUnpacking(b,this->requestingPortIdentity);
}

omnetpp::simtime_t& GptpPdelayRespFollowUp::getResponseOriginTimestamp()
{
    return this->responseOriginTimestamp;
}

void GptpPdelayRespFollowUp::setResponseOriginTimestamp(const omnetpp::simtime_t& responseOriginTimestamp)
{
    this->responseOriginTimestamp = responseOriginTimestamp;
}

PortIdentity& GptpPdelayRespFollowUp::getRequestingPortIdentity()
{
    return this->requestingPortIdentity;
}

void GptpPdelayRespFollowUp::setRequestingPortIdentity(const PortIdentity& requestingPortIdentity)
{
    this->requestingPortIdentity = requestingPortIdentity;
}

class GptpPdelayRespFollowUpDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpPdelayRespFollowUpDescriptor();
    virtual ~GptpPdelayRespFollowUpDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpPdelayRespFollowUpDescriptor)

GptpPdelayRespFollowUpDescriptor::GptpPdelayRespFollowUpDescriptor() : omnetpp::cClassDescriptor("cxj::GptpPdelayRespFollowUp", "cxj::GptpBase")
{
    propertynames = nullptr;
}

GptpPdelayRespFollowUpDescriptor::~GptpPdelayRespFollowUpDescriptor()
{
    delete[] propertynames;
}

bool GptpPdelayRespFollowUpDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayRespFollowUp *>(obj)!=nullptr;
}

const char **GptpPdelayRespFollowUpDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpPdelayRespFollowUpDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpPdelayRespFollowUpDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GptpPdelayRespFollowUpDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "responseOriginTimestamp",
        "requestingPortIdentity",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GptpPdelayRespFollowUpDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "responseOriginTimestamp")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requestingPortIdentity")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
        "PortIdentity",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayRespFollowUpDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpPdelayRespFollowUpDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = (GptpPdelayRespFollowUp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = (GptpPdelayRespFollowUp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayRespFollowUpDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = (GptpPdelayRespFollowUp *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getResponseOriginTimestamp(); return out.str();}
        case 1: {std::stringstream out; out << pp->getRequestingPortIdentity(); return out.str();}
        default: return "";
    }
}

bool GptpPdelayRespFollowUpDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = (GptpPdelayRespFollowUp *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        case 1: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

void *GptpPdelayRespFollowUpDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = (GptpPdelayRespFollowUp *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getResponseOriginTimestamp()); break;
        case 1: return (void *)(&pp->getRequestingPortIdentity()); break;
        default: return nullptr;
    }
}

GptpIngressTimeInd::GptpIngressTimeInd() : ::inet::TagBase()
{
}

GptpIngressTimeInd::GptpIngressTimeInd(const GptpIngressTimeInd& other) : ::inet::TagBase(other)
{
    copy(other);
}

GptpIngressTimeInd::~GptpIngressTimeInd()
{
}

GptpIngressTimeInd& GptpIngressTimeInd::operator=(const GptpIngressTimeInd& other)
{
    if (this==&other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void GptpIngressTimeInd::copy(const GptpIngressTimeInd& other)
{
    this->arrivalClockTime = other.arrivalClockTime;
}

void GptpIngressTimeInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::inet::TagBase&)*this);
    doParsimPacking(b,this->arrivalClockTime);
}

void GptpIngressTimeInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::inet::TagBase&)*this);
    doParsimUnpacking(b,this->arrivalClockTime);
}

omnetpp::simtime_t& GptpIngressTimeInd::getArrivalClockTime()
{
    return this->arrivalClockTime;
}

void GptpIngressTimeInd::setArrivalClockTime(const omnetpp::simtime_t& arrivalClockTime)
{
    this->arrivalClockTime = arrivalClockTime;
}

class GptpIngressTimeIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GptpIngressTimeIndDescriptor();
    virtual ~GptpIngressTimeIndDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GptpIngressTimeIndDescriptor)

GptpIngressTimeIndDescriptor::GptpIngressTimeIndDescriptor() : omnetpp::cClassDescriptor("cxj::GptpIngressTimeInd", "inet::TagBase")
{
    propertynames = nullptr;
}

GptpIngressTimeIndDescriptor::~GptpIngressTimeIndDescriptor()
{
    delete[] propertynames;
}

bool GptpIngressTimeIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpIngressTimeInd *>(obj)!=nullptr;
}

const char **GptpIngressTimeIndDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GptpIngressTimeIndDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GptpIngressTimeIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GptpIngressTimeIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GptpIngressTimeIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "arrivalClockTime",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GptpIngressTimeIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrivalClockTime")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GptpIngressTimeIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpIngressTimeIndDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GptpIngressTimeIndDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GptpIngressTimeIndDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GptpIngressTimeInd *pp = (GptpIngressTimeInd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GptpIngressTimeIndDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpIngressTimeInd *pp = (GptpIngressTimeInd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpIngressTimeIndDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GptpIngressTimeInd *pp = (GptpIngressTimeInd *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getArrivalClockTime(); return out.str();}
        default: return "";
    }
}

bool GptpIngressTimeIndDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GptpIngressTimeInd *pp = (GptpIngressTimeInd *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GptpIngressTimeIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(omnetpp::simtime_t));
        default: return nullptr;
    };
}

void *GptpIngressTimeIndDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GptpIngressTimeInd *pp = (GptpIngressTimeInd *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getArrivalClockTime()); break;
        default: return nullptr;
    }
}

} // namespace cxj

