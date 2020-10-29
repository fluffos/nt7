// group_quest:family 群组任务——门派入侵

#include <ansi.h>
#include "family.h"

void create()
{
        seteuid(getuid());

        if (!select_quest())
        {
                // destruct(this_object());
                return;
        }
}

//string prompt() { return HIR "【门派入侵】" NOR; }
string prompt() { return HIR "【门派】" NOR; }

int select_quest()
{
        int i;
        object *all_user;
        object ob,the_user;
        string p,*kp;
        mapping fam_map = ([]);

        // 遍历再现所有玩家，取得每个门派的在线玩家数，存入变量fam_map  family -> player_number
        foreach (object user in users())
        {
                if (! wizardp(user))
                {
                    p=query("family/family_name", user);
                    if (! stringp(p)) continue;
                    if (undefinedp(fam_map[p]))
                        fam_map[p] = ({ user });
                    else
                        fam_map[p] += ({ user });
                }
        }

        // MUD中没有属于任何一个门派的玩家
        if (!sizeof(fam_map))
            return 0;

        // 取得有玩家在线的门派名单
        kp = keys(fam_map);
        kp -= ({ "古村", "绝情谷", "云龙门", "华山剑宗" });
        if( !sizeof(kp) ) return 0;

        // 随即挑选一个门派
        p = kp[random(sizeof(kp))];

        // 根据这个门派在线的玩家数决定任务敌人数
        all = sizeof(fam_map[p]);
        if (all < 5) all = 5;
        if (all > 20) all = 30 - random(10);

        the_family = p;

        // 从这个门派中随机抽取三个玩家的名单，
        // 这里有一个问题，如果这个门派在线的玩家数少于3人怎么办？
        // 而且我也没有发现哪里使用到了name1, name2, name3，很奇怪
        // 我现在把他们放到一个name数组里面
        i = 3;
        while (i--)
        {
            if (sizeof(fam_map[p]))
            {
                name[i]=(query("name", fam_map[p][random(sizeof(fam_map[p]))]));
            }
            else
                name[i] = p + "弟子";
        }

        // 设置国家
        the_nation = "中国";
        the_enemy = GROUP_QUEST_D->get_enemy(); 

        // 选取一个故事
        story = all_story[random(sizeof(all_story))];

        return 1;
}

string create_tiaoxin()
{
        object ob;
        int i,lvl;
        string title;

        title = HIY + the_family + NOR + HIW + "仇家" + NOR + " " + HIY +
                        the_enemy + NOR;

        for (i = 0;i < all;i ++)
        {
                lvl = random(15) + 1;
                ob = GROUP_QUEST_D->create_npc(the_nation,lvl);
                GROUP_QUEST_D->place_npc(ob,"门派",the_family,lvl);
                set("title", title, ob);
                ob->random_move();
                ob->random_move();
                ob->random_move();
                ob->random_move();
        }
        GROUP_QUEST_D->set_enemy(all);
        return "大小喽罗高呼：『" + HIY + "【" + the_family + "】" + NOR + WHT + "的人快给我滚出来，大爷们今天要你们的好看！！』";
}

mixed query_quest_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg,"name1",name[0]);
                msg = replace_string(msg,"name2",name[1]);
                msg = replace_string(msg,"name3",name[2]);
                msg = replace_string(msg,"the_enemy",HIY + the_enemy + NOR + WHT);
                msg = replace_string(msg,"the_family",HIY + "【" + the_family + "】" + NOR + WHT);
        }
        return msg;
}
