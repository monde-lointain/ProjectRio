#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <optional>


class Tag
{
public:
    Tag() {}
    Tag(int in_id, std::string in_name, bool in_active, int in_date_created, std::string in_desc, int in_community_id, std::string in_type):
        id(in_id), 
        name(in_name),
        active(in_active),
        date_created(in_date_created),
        desc(in_desc),
        community_id(in_community_id),
        type(in_type)
        {}
    int id;
    std::string name;
    bool active;
    int date_created;
    std::string desc;
    int community_id;
    std::string type;
};


class TagSet
{
public:
    TagSet() {}
    TagSet(int in_id, std::string in_name, std::vector<Tag> in_tags):
        id(in_id),
        name(in_name),
        tags(in_tags)
        {}

    int id;
    std::string name;
    std::vector<Tag> tags;

    std::vector<std::string> tag_names_vector()
    {
        std::vector<std::string> names;
        for (Tag tag : tags) {
            names.push_back(tag.name);
        }
        return names;
    }

    std::vector<int> tag_ids_vector()
    {
        std::vector<int> ids;
        for (Tag tag : tags) {
            ids.push_back(tag.id);
        }
        return ids;
    }
};
