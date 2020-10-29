// cutable.c

#include <dbase.h>

// what I need ?

// mapping <parts> such as:
// ([ "head" : ({ 0, "头", "头颅", 0, ([ "eye" : "eye", "nose" : "nose" ...]),
//                "砍下", "/clone/misc/head", }),
//    "left middle finger" : ({ 0, "右手中指", "中指", "finger", 0, 0, 0 }), ])
// the mixed string *of part item is:
// 0. level of the body
// 1. unit of the part
// 2. the part name on owner,
// 3. the part name left from owner,
// 4. the part id left from owner
// 5. the association part & new id left with this part
// 6. the verb of cut
// 7. clone object of part cut
// if not clone object defined, I will clone "/clone/misc/part"
//
// <main_part_level> to show
//
// string string *<been_cut> such as:
// ({ "left_hand" })
//
// mapping <no_cut> that denied to cut

#define LEVEL           0
#define UNIT            1
#define NAME            2
#define NAME_LEFT       3
#define ID_LEFT         4
#define ASS_PART        5
#define VERB            6
#define CLONE           7

#define NOT_INCLUDE_THIS_PART   0
#define INCLUDE_THIS_PART       1

int is_cutable() { return 1; }

void include_part(object ob, string id, mixed *in_part, int include_this_part);

string *query_exclude_part() { return ({ }); }

int do_cut(object me, string arg)
{
        string *exist;
        string *cut;
        mapping parts;
        mixed *part;
        string default_clone;
        string msg;
        object weapon;
        object ob;

        if( !arg )
                return notify_fail("你要割下什么部位？\n");

        if( !mapp(parts = query("parts")) )
                return notify_fail("看来你是割不下来什么东西了。\n");

        exist = keys(parts);
        exist -= query_exclude_part();
        cut = query("been_cut");
        if( !cut ) cut = ({ });

        if( arg == "?" ) {
                int i;
                int count;
                count = 0;
                msg = this_object()->name() + "有以下部位可以割下来。\n";
                for( i = 0; i < sizeof(exist); i++ ) {
                        if( member_array(exist[i], cut) != -1 ||
                            query("no_cut/" + exist[i]) )
                                continue;
                        count++;
                        msg += sprintf("%-20s(%s)\n",
                                       parts[exist[i]][NAME], exist[i]);
                }
                if( !count )
                        msg = this_object()->name() + "已经没什么可以下刀的地方了。\n";
                write(msg);
                return 1;
        }

        part = parts[arg];
        if( !arrayp(part) )
                return notify_fail("你怎么也找不到你想割的部位。\n");

        if( member_array(arg, cut) != -1 )
                return notify_fail(part[NAME] + "已经被割走了。\n");

        if( msg = query("no_cut/" + arg) )
                return notify_fail(msg ? msg : "这样东西你割不下来。\n");

        if( time() < (int)query("who_get/time") && 
            query("id", me) != query("who_get/id") )
                return notify_fail("你还是稍等片刻再割吧。\n");

        default_clone = query("default_clone");
        if( weapon=query_temp("weapon", me)){
                msg = "$N举起手中的" + weapon->name() + "，“喀嚓”一下子把$n的" +
                      part[NAME] + "给" + (stringp(part[VERB]) ? part[VERB] : "割了下") +
                      "来。\n";
        } else if( me->query_skill("force") < 90 ) {
                message_vision("$N举起手来，对着$n的" + part[NAME] + "一掌"
                               "砍了下去，结果被震的“哇哇”怪叫了两声。\n",
                               me, this_object());
                write("好好练练内功再来吧！\n");
                return 1;
        } else
                msg = "$N举起手来，一下子就把$n的" + part[NAME] + "给" +
                      (stringp(part[VERB]) ? part[VERB] : "切了下") + "来。\n";

        message_vision(msg, me, this_object());
        ob = new(stringp(part[CLONE]) ? part[CLONE] : default_clone);
        ob->set_name(stringp(part[NAME_LEFT]) ? part[NAME_LEFT] : part[NAME],
                     ({ stringp(part[ID_LEFT]) ? part[ID_LEFT] : arg }));
        set("unit", part[UNIT], ob);
        set("long", "一"+part[UNIT]+"被人割下来的"+ob->name()+"。\n", ob);
        set("default_clone", default_clone, ob);
        set("main_part_level", part[LEVEL]+1, ob);
        if( ob->is_cutable() )
                set("been_cut", ({}), ob);
        ob->set_from(this_object());
        // ob->move(environment());
        if( !ob->move(me) ) 
                ob->move(environment());

        // seperate the part cut
        cut += ({ arg });
        set("been_cut", cut);

        // seperate the association part
        if( query_temp("quest_corpse", this_object()) )
                destruct(this_object());
        else
        include_part(ob, arg, 0, NOT_INCLUDE_THIS_PART);
        return 1;
}

string extra_desc()
{
        string msg;
        string *cut;
        mixed *part;
        int flag;
        int i;

        msg = "";
        if( !arrayp(cut = query("been_cut")) )
                return msg;
        flag = 0;
        for( i = 0; i < sizeof(cut); i++ ) {
                part = query("parts/" + cut[i]);
                if( part[LEVEL] > query("main_part_level") )
                        continue;
                if( !flag ) {
                        msg += "不过它的" + part[NAME];
                        flag++;
                } else
                        msg += "、" + part[NAME];
        }
        if( flag ) msg += "已经不见了。\n";
        return msg;
}

void include_part(object ob, string id, mixed *in_part, int include_this_part)
{
        string *cut;
        string *ass;
        mixed  *srcpart;
        mixed  *part;
        string new_id;
        mapping assmap;
        int i;

        srcpart = query("parts/" + id);
        if( !arrayp(srcpart) )
                return;
        part = allocate(sizeof(srcpart));
        for( i = 0; i < sizeof(srcpart); i++ )
                part[i] = srcpart[i];
        part[ASS_PART] = allocate_mapping(sizeof(srcpart[ASS_PART]));
        if( include_this_part ) {
                part[NAME] = part[NAME_LEFT];
                new_id = in_part[ASS_PART][id];
                set("parts/"+new_id, part, ob);
                if( member_array(id, cut = query("been_cut")) != -1 )
                        set("been_cut",query("been_cut",  ob)+({new_id}), ob);
                set("been_cut", cut + ({ id }));
        }
        if( mapp(assmap = srcpart[ASS_PART]) ) {
                // set the association part
                ass = keys(assmap);
                for( i = 0; i < sizeof(ass); i++ ) {
                        include_part(ob, ass[i], srcpart, INCLUDE_THIS_PART);
                        new_id = assmap[ass[i]];
                        part[ASS_PART][new_id] = new_id;
                        if( query("no_cut/" + ass[i]) )
                                set("no_cut/"+new_id, query("no_cut/"+ass[i]), ob);
                }
        }
}
