// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#include "include/message.pb.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite.h>

#include <algorithm>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_message_2eproto ::PROTOBUF_NAMESPACE_ID::
    internal::SCCInfo<0>
        scc_info_MemberUpdate_message_2eproto;
namespace membership {
class MemberUpdateDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<MemberUpdate>
      _instance;
} _MemberUpdate_default_instance_;
class MemberFullStateDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<MemberFullState>
      _instance;
} _MemberFullState_default_instance_;
}  // namespace membership
static void InitDefaultsscc_info_MemberFullState_message_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::membership::_MemberFullState_default_instance_;
    new (ptr)::membership::MemberFullState();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::membership::MemberFullState::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1>
    scc_info_MemberFullState_message_2eproto = {
        {ATOMIC_VAR_INIT(
             ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized),
         1, InitDefaultsscc_info_MemberFullState_message_2eproto},
        {
            &scc_info_MemberUpdate_message_2eproto.base,
        }};

static void InitDefaultsscc_info_MemberUpdate_message_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::membership::_MemberUpdate_default_instance_;
    new (ptr)::membership::MemberUpdate();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::membership::MemberUpdate::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0>
    scc_info_MemberUpdate_message_2eproto = {
        {ATOMIC_VAR_INIT(
             ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized),
         0, InitDefaultsscc_info_MemberUpdate_message_2eproto},
        {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_message_2eproto[2];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
    file_level_enum_descriptors_message_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const**
    file_level_service_descriptors_message_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32
    TableStruct_message_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, _has_bits_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, name_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, ip_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, port_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, status_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberUpdate, incarnation_),
        0,
        1,
        2,
        3,
        4,
        PROTOBUF_FIELD_OFFSET(::membership::MemberFullState, _has_bits_),
        PROTOBUF_FIELD_OFFSET(::membership::MemberFullState,
                              _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        PROTOBUF_FIELD_OFFSET(::membership::MemberFullState, states_),
        ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, 10, sizeof(::membership::MemberUpdate)},
        {15, 21, sizeof(::membership::MemberFullState)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const* const file_default_instances[] =
    {
        reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(
            &::membership::_MemberUpdate_default_instance_),
        reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(
            &::membership::_MemberFullState_default_instance_),
};

const char
    descriptor_table_protodef_message_2eproto[] PROTOBUF_SECTION_VARIABLE(
        protodesc_cold) =
        "\n\rmessage.proto\022\nmembership\"\244\001\n\014MemberUp"
        "date\022\014\n\004name\030\001 \002(\t\022\n\n\002ip\030\002 "
        "\002(\t\022\014\n\004port\030\003"
        " \002(\005\0225\n\006status\030\004 \002(\0162%.membership.Member"
        "Update.MemberStatus\022\023\n\013incarnation\030\005 \002(\005"
        "\" "
        "\n\014MemberStatus\022\006\n\002UP\020\000\022\010\n\004DOWN\020\001\""
        ";\n\017Me"
        "mberFullState\022(\n\006states\030\001 \003(\0132\030.membersh"
        "ip.MemberUpdate";
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* const
    descriptor_table_message_2eproto_deps[1] = {};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase* const
    descriptor_table_message_2eproto_sccs[2] = {
        &scc_info_MemberFullState_message_2eproto.base,
        &scc_info_MemberUpdate_message_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag
    descriptor_table_message_2eproto_once;
static bool descriptor_table_message_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_message_2eproto = {
        &descriptor_table_message_2eproto_initialized,
        descriptor_table_protodef_message_2eproto,
        "message.proto",
        255,
        &descriptor_table_message_2eproto_once,
        descriptor_table_message_2eproto_sccs,
        descriptor_table_message_2eproto_deps,
        2,
        0,
        schemas,
        file_default_instances,
        TableStruct_message_2eproto::offsets,
        file_level_metadata_message_2eproto,
        2,
        file_level_enum_descriptors_message_2eproto,
        file_level_service_descriptors_message_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_message_2eproto =
    (::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(
         &descriptor_table_message_2eproto),
     true);
namespace membership {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
MemberUpdate_MemberStatus_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_message_2eproto);
  return file_level_enum_descriptors_message_2eproto[0];
}
bool MemberUpdate_MemberStatus_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr MemberUpdate_MemberStatus MemberUpdate::UP;
constexpr MemberUpdate_MemberStatus MemberUpdate::DOWN;
constexpr MemberUpdate_MemberStatus MemberUpdate::MemberStatus_MIN;
constexpr MemberUpdate_MemberStatus MemberUpdate::MemberStatus_MAX;
constexpr int MemberUpdate::MemberStatus_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void MemberUpdate::InitAsDefaultInstance() {}
class MemberUpdate::_Internal {
 public:
  using HasBits = decltype(std::declval<MemberUpdate>()._has_bits_);
  static void set_has_name(HasBits* has_bits) { (*has_bits)[0] |= 1u; }
  static void set_has_ip(HasBits* has_bits) { (*has_bits)[0] |= 2u; }
  static void set_has_port(HasBits* has_bits) { (*has_bits)[0] |= 4u; }
  static void set_has_status(HasBits* has_bits) { (*has_bits)[0] |= 8u; }
  static void set_has_incarnation(HasBits* has_bits) { (*has_bits)[0] |= 16u; }
};

MemberUpdate::MemberUpdate()
    : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:membership.MemberUpdate)
}
MemberUpdate::MemberUpdate(const MemberUpdate& from)
    : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(
        &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
        from.name_);
  }
  ip_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.has_ip()) {
    ip_.AssignWithDefault(
        &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
        from.ip_);
  }
  ::memcpy(&port_, &from.port_,
           static_cast<size_t>(reinterpret_cast<char*>(&incarnation_) -
                               reinterpret_cast<char*>(&port_)) +
               sizeof(incarnation_));
  // @@protoc_insertion_point(copy_constructor:membership.MemberUpdate)
}

void MemberUpdate::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &scc_info_MemberUpdate_message_2eproto.base);
  name_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ip_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&port_, 0,
           static_cast<size_t>(reinterpret_cast<char*>(&incarnation_) -
                               reinterpret_cast<char*>(&port_)) +
               sizeof(incarnation_));
}

MemberUpdate::~MemberUpdate() {
  // @@protoc_insertion_point(destructor:membership.MemberUpdate)
  SharedDtor();
}

void MemberUpdate::SharedDtor() {
  name_.DestroyNoArena(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ip_.DestroyNoArena(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void MemberUpdate::SetCachedSize(int size) const { _cached_size_.Set(size); }
const MemberUpdate& MemberUpdate::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &::scc_info_MemberUpdate_message_2eproto.base);
  return *internal_default_instance();
}

void MemberUpdate::Clear() {
  // @@protoc_insertion_point(message_clear_start:membership.MemberUpdate)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      name_.ClearNonDefaultToEmptyNoArena();
    }
    if (cached_has_bits & 0x00000002u) {
      ip_.ClearNonDefaultToEmptyNoArena();
    }
  }
  if (cached_has_bits & 0x0000001cu) {
    ::memset(&port_, 0,
             static_cast<size_t>(reinterpret_cast<char*>(&incarnation_) -
                                 reinterpret_cast<char*>(&port_)) +
                 sizeof(incarnation_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* MemberUpdate::_InternalParse(
    const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) \
  if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::
              InlineGreedyStringParserUTF8Verify(
                  mutable_name(), ptr, ctx, "membership.MemberUpdate.name");
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required string ip = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::
              InlineGreedyStringParserUTF8Verify(mutable_ip(), ptr, ctx,
                                                 "membership.MemberUpdate.ip");
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required int32 port = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_port(&has_bits);
          port_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // required .membership.MemberUpdate.MemberStatus status = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val =
              ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(
                  ::membership::MemberUpdate_MemberStatus_IsValid(val))) {
            set_status(
                static_cast<::membership::MemberUpdate_MemberStatus>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(
                4, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      // required int32 incarnation = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          _Internal::set_has_incarnation(&has_bits);
          incarnation_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }    // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool MemberUpdate::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) \
  if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:membership.MemberUpdate)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p =
        input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(
            tag)) {
      // required string name = 1;
      case 1: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
              input, this->mutable_name()));
          ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
              VerifyUTF8StringNamedField(
                  this->name().data(), static_cast<int>(this->name().length()),
                  ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::PARSE,
                  "membership.MemberUpdate.name");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required string ip = 2;
      case 2: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
              input, this->mutable_ip()));
          ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
              VerifyUTF8StringNamedField(
                  this->ip().data(), static_cast<int>(this->ip().length()),
                  ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::PARSE,
                  "membership.MemberUpdate.ip");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 port = 3;
      case 3: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (24 & 0xFF)) {
          _Internal::set_has_port(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
               ::PROTOBUF_NAMESPACE_ID::int32,
               ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
              input, &port_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .membership.MemberUpdate.MemberStatus status = 4;
      case 4: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (32 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
               int,
               ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
              input, &value)));
          if (::membership::MemberUpdate_MemberStatus_IsValid(value)) {
            set_status(
                static_cast<::membership::MemberUpdate_MemberStatus>(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                4, static_cast<::PROTOBUF_NAMESPACE_ID::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 incarnation = 5;
      case 5: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (40 & 0xFF)) {
          _Internal::set_has_incarnation(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
               ::PROTOBUF_NAMESPACE_ID::int32,
               ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
              input, &incarnation_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
            input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:membership.MemberUpdate)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:membership.MemberUpdate)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void MemberUpdate::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:membership.MemberUpdate)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
        this->name().data(), static_cast<int>(this->name().length()),
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
        "membership.MemberUpdate.name");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
        1, this->name(), output);
  }

  // required string ip = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
        this->ip().data(), static_cast<int>(this->ip().length()),
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
        "membership.MemberUpdate.ip");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
        2, this->ip(), output);
  }

  // required int32 port = 3;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(
        3, this->port(), output);
  }

  // required .membership.MemberUpdate.MemberStatus status = 4;
  if (cached_has_bits & 0x00000008u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
        4, this->status(), output);
  }

  // required int32 incarnation = 5;
  if (cached_has_bits & 0x00000010u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(
        5, this->incarnation(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:membership.MemberUpdate)
}

::PROTOBUF_NAMESPACE_ID::uint8*
MemberUpdate::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:membership.MemberUpdate)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
        this->name().data(), static_cast<int>(this->name().length()),
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
        "membership.MemberUpdate.name");
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
            1, this->name(), target);
  }

  // required string ip = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
        this->ip().data(), static_cast<int>(this->ip().length()),
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
        "membership.MemberUpdate.ip");
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
            2, this->ip(), target);
  }

  // required int32 port = 3;
  if (cached_has_bits & 0x00000004u) {
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(
            3, this->port(), target);
  }

  // required .membership.MemberUpdate.MemberStatus status = 4;
  if (cached_has_bits & 0x00000008u) {
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
            4, this->status(), target);
  }

  // required int32 incarnation = 5;
  if (cached_has_bits & 0x00000010u) {
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(
            5, this->incarnation(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
        SerializeUnknownFieldsToArray(_internal_metadata_.unknown_fields(),
                                      target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:membership.MemberUpdate)
  return target;
}

size_t MemberUpdate::RequiredFieldsByteSizeFallback() const {
  // @@protoc_insertion_point(required_fields_byte_size_fallback_start:membership.MemberUpdate)
  size_t total_size = 0;

  if (has_name()) {
    // required string name = 1;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                this->name());
  }

  if (has_ip()) {
    // required string ip = 2;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                this->ip());
  }

  if (has_port()) {
    // required int32 port = 3;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
                this->port());
  }

  if (has_status()) {
    // required .membership.MemberUpdate.MemberStatus status = 4;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(
                this->status());
  }

  if (has_incarnation()) {
    // required int32 incarnation = 5;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
                this->incarnation());
  }

  return total_size;
}
size_t MemberUpdate::ByteSizeLong() const {
  // @@protoc_insertion_point(message_byte_size_start:membership.MemberUpdate)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
            _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x0000001f) ^ 0x0000001f) ==
      0) {  // All required fields are present.
    // required string name = 1;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                this->name());

    // required string ip = 2;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                this->ip());

    // required int32 port = 3;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
                this->port());

    // required .membership.MemberUpdate.MemberStatus status = 4;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(
                this->status());

    // required int32 incarnation = 5;
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
                this->incarnation());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MemberUpdate::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_merge_from_start:membership.MemberUpdate)
  GOOGLE_DCHECK_NE(&from, this);
  const MemberUpdate* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MemberUpdate>(&from);
  if (source == nullptr) {
    // @@protoc_insertion_point(generalized_merge_from_cast_fail:membership.MemberUpdate)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
    // @@protoc_insertion_point(generalized_merge_from_cast_success:membership.MemberUpdate)
    MergeFrom(*source);
  }
}

void MemberUpdate::MergeFrom(const MemberUpdate& from) {
  // @@protoc_insertion_point(class_specific_merge_from_start:membership.MemberUpdate)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      name_.AssignWithDefault(
          &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
          from.name_);
    }
    if (cached_has_bits & 0x00000002u) {
      _has_bits_[0] |= 0x00000002u;
      ip_.AssignWithDefault(
          &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
          from.ip_);
    }
    if (cached_has_bits & 0x00000004u) {
      port_ = from.port_;
    }
    if (cached_has_bits & 0x00000008u) {
      status_ = from.status_;
    }
    if (cached_has_bits & 0x00000010u) {
      incarnation_ = from.incarnation_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void MemberUpdate::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_copy_from_start:membership.MemberUpdate)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MemberUpdate::CopyFrom(const MemberUpdate& from) {
  // @@protoc_insertion_point(class_specific_copy_from_start:membership.MemberUpdate)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MemberUpdate::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  return true;
}

void MemberUpdate::InternalSwap(MemberUpdate* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  name_.Swap(&other->name_,
             &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
             GetArenaNoVirtual());
  ip_.Swap(&other->ip_,
           &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
           GetArenaNoVirtual());
  swap(port_, other->port_);
  swap(status_, other->status_);
  swap(incarnation_, other->incarnation_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MemberUpdate::GetMetadata() const {
  return GetMetadataStatic();
}

// ===================================================================

void MemberFullState::InitAsDefaultInstance() {}
class MemberFullState::_Internal {
 public:
  using HasBits = decltype(std::declval<MemberFullState>()._has_bits_);
};

MemberFullState::MemberFullState()
    : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:membership.MemberFullState)
}
MemberFullState::MemberFullState(const MemberFullState& from)
    : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      states_(from.states_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:membership.MemberFullState)
}

void MemberFullState::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &scc_info_MemberFullState_message_2eproto.base);
}

MemberFullState::~MemberFullState() {
  // @@protoc_insertion_point(destructor:membership.MemberFullState)
  SharedDtor();
}

void MemberFullState::SharedDtor() {}

void MemberFullState::SetCachedSize(int size) const { _cached_size_.Set(size); }
const MemberFullState& MemberFullState::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &::scc_info_MemberFullState_message_2eproto.base);
  return *internal_default_instance();
}

void MemberFullState::Clear() {
  // @@protoc_insertion_point(message_clear_start:membership.MemberFullState)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  states_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* MemberFullState::_InternalParse(
    const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) \
  if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .membership.MemberUpdate states = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(add_states(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<
                       ::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 10);
        } else
          goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }    // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool MemberFullState::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) \
  if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:membership.MemberFullState)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p =
        input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(
            tag)) {
      // repeated .membership.MemberUpdate states = 1;
      case 1: {
        if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
              input, add_states()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
            input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:membership.MemberFullState)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:membership.MemberFullState)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void MemberFullState::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:membership.MemberFullState)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  // repeated .membership.MemberUpdate states = 1;
  for (unsigned int i = 0, n = static_cast<unsigned int>(this->states_size());
       i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
        1, this->states(static_cast<int>(i)), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:membership.MemberFullState)
}

::PROTOBUF_NAMESPACE_ID::uint8*
MemberFullState::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:membership.MemberFullState)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  // repeated .membership.MemberUpdate states = 1;
  for (unsigned int i = 0, n = static_cast<unsigned int>(this->states_size());
       i < n; i++) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessageToArray(1, this->states(static_cast<int>(i)),
                                    target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
        SerializeUnknownFieldsToArray(_internal_metadata_.unknown_fields(),
                                      target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:membership.MemberFullState)
  return target;
}

size_t MemberFullState::ByteSizeLong() const {
  // @@protoc_insertion_point(message_byte_size_start:membership.MemberFullState)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
            _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  // repeated .membership.MemberUpdate states = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->states_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
          ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
              this->states(static_cast<int>(i)));
    }
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MemberFullState::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_merge_from_start:membership.MemberFullState)
  GOOGLE_DCHECK_NE(&from, this);
  const MemberFullState* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MemberFullState>(&from);
  if (source == nullptr) {
    // @@protoc_insertion_point(generalized_merge_from_cast_fail:membership.MemberFullState)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
    // @@protoc_insertion_point(generalized_merge_from_cast_success:membership.MemberFullState)
    MergeFrom(*source);
  }
}

void MemberFullState::MergeFrom(const MemberFullState& from) {
  // @@protoc_insertion_point(class_specific_merge_from_start:membership.MemberFullState)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  states_.MergeFrom(from.states_);
}

void MemberFullState::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_copy_from_start:membership.MemberFullState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MemberFullState::CopyFrom(const MemberFullState& from) {
  // @@protoc_insertion_point(class_specific_copy_from_start:membership.MemberFullState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MemberFullState::IsInitialized() const {
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(this->states()))
    return false;
  return true;
}

void MemberFullState::InternalSwap(MemberFullState* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  CastToBase(&states_)->InternalSwap(CastToBase(&other->states_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MemberFullState::GetMetadata() const {
  return GetMetadataStatic();
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace membership
PROTOBUF_NAMESPACE_OPEN
template <>
PROTOBUF_NOINLINE ::membership::MemberUpdate*
Arena::CreateMaybeMessage<::membership::MemberUpdate>(Arena* arena) {
  return Arena::CreateInternal<::membership::MemberUpdate>(arena);
}
template <>
PROTOBUF_NOINLINE ::membership::MemberFullState*
Arena::CreateMaybeMessage<::membership::MemberFullState>(Arena* arena) {
  return Arena::CreateInternal<::membership::MemberFullState>(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
