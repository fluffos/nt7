// group_quest:party1 群组任务——帮派挑衅

#include <ansi.h>
#include "party.h"

void create()
{
        seteuid(getuid());

        if (!select_quest())
        {
                // destruct(this_object());
                return;
        }
}

//string prompt() { return HIR "【帮派挑衅】" NOR; }
string prompt() { return HIR "【帮派】" NOR; }

int select_quest()
{
        int i;
        object *all_user;
        object ob,the_user;
        string p,*kp;
        mapping party_map = ([]);
        
        all_user = users();
        all_user = filter_array(all_user,(: query("bunch", $1) :));
        all_user = filter_array(all_user,(: not_wizard :));
        for (i = 0;i < sizeof (all_user);i ++)
        {
                p=query("bunch/bunch_name", all_user[i]);
                if (!stringp(p)) continue;
                if (!party_map[p])
                        party_map[p] = 1;
                else
                        party_map[p] += 1;
        }                                
        kp = keys(party_map);
        for (i = 0;i < sizeof(kp);i++)
                if (party_map[kp[i]] < 5)
                        map_delete(party_map,kp[i]);
        if (!sizeof(party_map)) return 0;
        kp = keys(party_map);
        p = kp[random(sizeof(kp))];
        all = party_map[p] * 2;
        if (all < 10) all = 20 - random(11);
        if (all > 20) all = 30 - random(10);
        the_party = p;

        all_user = filter_array(all_user,(: objectp($1) :));
        all_user = filter_array(all_user,(: $1->query_bunch() == $2 :),p);
        the_user = all_user[random(sizeof(all_user))];
        name1 = the_user->name(1);
        all_user -= ({ the_user });
        the_user = all_user[random(sizeof(all_user))];
        name2 = the_user->name(1);
        all_user -= ({ the_user });
        the_user = all_user[random(sizeof(all_user))];
        name3 = the_user->name(1);
        all_user = 0;

        if (!(place = GROUP_QUEST_D->query_place()))
                return 0;

        the_nation = "中国";

        story = all_story[random(sizeof(all_story))];

        return 1;
}

string create_tiaoxin()
{
        object ob;
        int i,lvl;
        string title;

        the_enemy = GROUP_QUEST_D->get_enemy();
        title = HIY + the_party + NOR + HIW + "仇家" + NOR + " " + HIY + 
                        the_enemy + NOR;

        for (i = 0;i < all;i ++)
        {
                lvl = random(15) + 1;
                ob = GROUP_QUEST_D->create_npc(the_nation,lvl);
                GROUP_QUEST_D->place_npc(ob,"帮派",the_party,lvl,place);
                set("title", title, ob);
                ob->random_move();
                ob->random_move();
                ob->random_move();
                ob->random_move();
        }
        GROUP_QUEST_D->set_enemy(all);
        return "大小喽罗高呼：『" + HIY + "【" + the_party + "】" + NOR + WHT + "的人快给我滚出来，大爷们今天要你们的好看！！』";
}

mixed query_quest_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg,"name1",name1);
                msg = replace_string(msg,"name2",name2);
                msg = replace_string(msg,"name3",name3);
                msg = replace_string(msg,"place",HIY + place + NOR + WHT);
                msg = replace_string(msg,"the_enemy",HIY + the_enemy + NOR + WHT);
                msg = replace_string(msg,"the_party",HIY + "【" + the_party + "】" + NOR + WHT);
        }
        return msg;
}

int not_wizard(object ob)
{
        if (wizardp(ob)) return 0;
        return 1;
}
