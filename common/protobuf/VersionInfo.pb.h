// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: VersionInfo.proto

#ifndef PROTOBUF_VersionInfo_2eproto__INCLUDED
#define PROTOBUF_VersionInfo_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_VersionInfo_2eproto();
void protobuf_AssignDesc_VersionInfo_2eproto();
void protobuf_ShutdownFile_VersionInfo_2eproto();

class VersionInfo;
class VersionInfos;

// ===================================================================

class VersionInfo : public ::google::protobuf::Message {
 public:
  VersionInfo();
  virtual ~VersionInfo();

  VersionInfo(const VersionInfo& from);

  inline VersionInfo& operator=(const VersionInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const VersionInfo& default_instance();

  void Swap(VersionInfo* other);

  // implements Message ----------------------------------------------

  VersionInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VersionInfo& from);
  void MergeFrom(const VersionInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // required string url = 2;
  inline bool has_url() const;
  inline void clear_url();
  static const int kUrlFieldNumber = 2;
  inline const ::std::string& url() const;
  inline void set_url(const ::std::string& value);
  inline void set_url(const char* value);
  inline void set_url(const char* value, size_t size);
  inline ::std::string* mutable_url();
  inline ::std::string* release_url();
  inline void set_allocated_url(::std::string* url);

  // required string name = 3;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 3;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required string md5 = 4;
  inline bool has_md5() const;
  inline void clear_md5();
  static const int kMd5FieldNumber = 4;
  inline const ::std::string& md5() const;
  inline void set_md5(const ::std::string& value);
  inline void set_md5(const char* value);
  inline void set_md5(const char* value, size_t size);
  inline ::std::string* mutable_md5();
  inline ::std::string* release_md5();
  inline void set_allocated_md5(::std::string* md5);

  // required string msg = 5;
  inline bool has_msg() const;
  inline void clear_msg();
  static const int kMsgFieldNumber = 5;
  inline const ::std::string& msg() const;
  inline void set_msg(const ::std::string& value);
  inline void set_msg(const char* value);
  inline void set_msg(const char* value, size_t size);
  inline ::std::string* mutable_msg();
  inline ::std::string* release_msg();
  inline void set_allocated_msg(::std::string* msg);

  // @@protoc_insertion_point(class_scope:VersionInfo)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_url();
  inline void clear_has_url();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_md5();
  inline void clear_has_md5();
  inline void set_has_msg();
  inline void clear_has_msg();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* url_;
  ::std::string* name_;
  ::std::string* md5_;
  ::std::string* msg_;
  ::google::protobuf::int32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_VersionInfo_2eproto();
  friend void protobuf_AssignDesc_VersionInfo_2eproto();
  friend void protobuf_ShutdownFile_VersionInfo_2eproto();

  void InitAsDefaultInstance();
  static VersionInfo* default_instance_;
};
// -------------------------------------------------------------------

class VersionInfos : public ::google::protobuf::Message {
 public:
  VersionInfos();
  virtual ~VersionInfos();

  VersionInfos(const VersionInfos& from);

  inline VersionInfos& operator=(const VersionInfos& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const VersionInfos& default_instance();

  void Swap(VersionInfos* other);

  // implements Message ----------------------------------------------

  VersionInfos* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const VersionInfos& from);
  void MergeFrom(const VersionInfos& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .VersionInfo data = 1;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 1;
  inline const ::VersionInfo& data(int index) const;
  inline ::VersionInfo* mutable_data(int index);
  inline ::VersionInfo* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::VersionInfo >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::VersionInfo >*
      mutable_data();

  // @@protoc_insertion_point(class_scope:VersionInfos)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::VersionInfo > data_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_VersionInfo_2eproto();
  friend void protobuf_AssignDesc_VersionInfo_2eproto();
  friend void protobuf_ShutdownFile_VersionInfo_2eproto();

  void InitAsDefaultInstance();
  static VersionInfos* default_instance_;
};
// ===================================================================


// ===================================================================

// VersionInfo

// required int32 id = 1;
inline bool VersionInfo::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void VersionInfo::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void VersionInfo::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void VersionInfo::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 VersionInfo::id() const {
  return id_;
}
inline void VersionInfo::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required string url = 2;
inline bool VersionInfo::has_url() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void VersionInfo::set_has_url() {
  _has_bits_[0] |= 0x00000002u;
}
inline void VersionInfo::clear_has_url() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void VersionInfo::clear_url() {
  if (url_ != &::google::protobuf::internal::kEmptyString) {
    url_->clear();
  }
  clear_has_url();
}
inline const ::std::string& VersionInfo::url() const {
  return *url_;
}
inline void VersionInfo::set_url(const ::std::string& value) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(value);
}
inline void VersionInfo::set_url(const char* value) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(value);
}
inline void VersionInfo::set_url(const char* value, size_t size) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* VersionInfo::mutable_url() {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  return url_;
}
inline ::std::string* VersionInfo::release_url() {
  clear_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = url_;
    url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void VersionInfo::set_allocated_url(::std::string* url) {
  if (url_ != &::google::protobuf::internal::kEmptyString) {
    delete url_;
  }
  if (url) {
    set_has_url();
    url_ = url;
  } else {
    clear_has_url();
    url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string name = 3;
inline bool VersionInfo::has_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void VersionInfo::set_has_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void VersionInfo::clear_has_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void VersionInfo::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& VersionInfo::name() const {
  return *name_;
}
inline void VersionInfo::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void VersionInfo::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void VersionInfo::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* VersionInfo::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* VersionInfo::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void VersionInfo::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string md5 = 4;
inline bool VersionInfo::has_md5() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void VersionInfo::set_has_md5() {
  _has_bits_[0] |= 0x00000008u;
}
inline void VersionInfo::clear_has_md5() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void VersionInfo::clear_md5() {
  if (md5_ != &::google::protobuf::internal::kEmptyString) {
    md5_->clear();
  }
  clear_has_md5();
}
inline const ::std::string& VersionInfo::md5() const {
  return *md5_;
}
inline void VersionInfo::set_md5(const ::std::string& value) {
  set_has_md5();
  if (md5_ == &::google::protobuf::internal::kEmptyString) {
    md5_ = new ::std::string;
  }
  md5_->assign(value);
}
inline void VersionInfo::set_md5(const char* value) {
  set_has_md5();
  if (md5_ == &::google::protobuf::internal::kEmptyString) {
    md5_ = new ::std::string;
  }
  md5_->assign(value);
}
inline void VersionInfo::set_md5(const char* value, size_t size) {
  set_has_md5();
  if (md5_ == &::google::protobuf::internal::kEmptyString) {
    md5_ = new ::std::string;
  }
  md5_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* VersionInfo::mutable_md5() {
  set_has_md5();
  if (md5_ == &::google::protobuf::internal::kEmptyString) {
    md5_ = new ::std::string;
  }
  return md5_;
}
inline ::std::string* VersionInfo::release_md5() {
  clear_has_md5();
  if (md5_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = md5_;
    md5_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void VersionInfo::set_allocated_md5(::std::string* md5) {
  if (md5_ != &::google::protobuf::internal::kEmptyString) {
    delete md5_;
  }
  if (md5) {
    set_has_md5();
    md5_ = md5;
  } else {
    clear_has_md5();
    md5_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string msg = 5;
inline bool VersionInfo::has_msg() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void VersionInfo::set_has_msg() {
  _has_bits_[0] |= 0x00000010u;
}
inline void VersionInfo::clear_has_msg() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void VersionInfo::clear_msg() {
  if (msg_ != &::google::protobuf::internal::kEmptyString) {
    msg_->clear();
  }
  clear_has_msg();
}
inline const ::std::string& VersionInfo::msg() const {
  return *msg_;
}
inline void VersionInfo::set_msg(const ::std::string& value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void VersionInfo::set_msg(const char* value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void VersionInfo::set_msg(const char* value, size_t size) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* VersionInfo::mutable_msg() {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  return msg_;
}
inline ::std::string* VersionInfo::release_msg() {
  clear_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = msg_;
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void VersionInfo::set_allocated_msg(::std::string* msg) {
  if (msg_ != &::google::protobuf::internal::kEmptyString) {
    delete msg_;
  }
  if (msg) {
    set_has_msg();
    msg_ = msg;
  } else {
    clear_has_msg();
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// VersionInfos

// repeated .VersionInfo data = 1;
inline int VersionInfos::data_size() const {
  return data_.size();
}
inline void VersionInfos::clear_data() {
  data_.Clear();
}
inline const ::VersionInfo& VersionInfos::data(int index) const {
  return data_.Get(index);
}
inline ::VersionInfo* VersionInfos::mutable_data(int index) {
  return data_.Mutable(index);
}
inline ::VersionInfo* VersionInfos::add_data() {
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::VersionInfo >&
VersionInfos::data() const {
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::VersionInfo >*
VersionInfos::mutable_data() {
  return &data_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_VersionInfo_2eproto__INCLUDED
