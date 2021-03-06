// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PUBSUB_TOPIC_MUTATION_BUILDER_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PUBSUB_TOPIC_MUTATION_BUILDER_H

#include "google/cloud/pubsub/topic.h"
#include "google/cloud/pubsub/version.h"
#include <google/pubsub/v1/pubsub.pb.h>
#include <set>

namespace google {
namespace cloud {
namespace pubsub {
inline namespace GOOGLE_CLOUD_CPP_PUBSUB_NS {

/**
 * Create a Cloud Pub/Sub topic configuration.
 */
class TopicMutationBuilder {
 public:
  explicit TopicMutationBuilder(Topic const& topic) {
    proto_.set_name(topic.FullName());
  }

  google::pubsub::v1::Topic BuildCreateMutation() &&;

  google::pubsub::v1::UpdateTopicRequest BuildUpdateMutation() &&;

  TopicMutationBuilder& add_label(std::string const& key,
                                  std::string const& value) & {
    using value_type = protobuf::Map<std::string, std::string>::value_type;
    proto_.mutable_labels()->insert(value_type(key, value));
    paths_.insert("labels");
    return *this;
  }
  TopicMutationBuilder&& add_label(std::string const& key,
                                   std::string const& value) && {
    return std::move(add_label(key, value));
  }

  TopicMutationBuilder& clear_labels() & {
    proto_.clear_labels();
    paths_.insert("labels");
    return *this;
  }
  TopicMutationBuilder&& clear_labels() && { return std::move(clear_labels()); }

  TopicMutationBuilder& add_allowed_persistence_region(std::string region) & {
    proto_.mutable_message_storage_policy()->add_allowed_persistence_regions(
        std::move(region));
    paths_.insert("message_storage_policy");
    return *this;
  }
  TopicMutationBuilder&& add_allowed_persistence_region(std::string region) && {
    return std::move(add_allowed_persistence_region(std::move(region)));
  }

  TopicMutationBuilder& clear_allowed_persistence_regions() & {
    proto_.mutable_message_storage_policy()
        ->clear_allowed_persistence_regions();
    paths_.insert("message_storage_policy");
    return *this;
  }
  TopicMutationBuilder&& clear_allowed_persistence_regions() && {
    return std::move(clear_allowed_persistence_regions());
  }

  TopicMutationBuilder& set_kms_key_name(std::string key_name) & {
    proto_.set_kms_key_name(std::move(key_name));
    paths_.insert("kms_key_name");
    return *this;
  }
  TopicMutationBuilder&& set_kms_key_name(std::string key_name) && {
    return std::move(set_kms_key_name(std::move(key_name)));
  }

 private:
  google::pubsub::v1::Topic proto_;
  std::set<std::string> paths_;
};

}  // namespace GOOGLE_CLOUD_CPP_PUBSUB_NS
}  // namespace pubsub
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_PUBSUB_TOPIC_MUTATION_BUILDER_H
