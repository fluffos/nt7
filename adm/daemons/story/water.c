// story:witer 圣沐

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "红孩儿：菩萨！大事不好了！唐僧他们又惹祸了。",
        "观音：哦？他们现在应该在五庄观，出了什么事？",
        "红孩儿：他…他们在五庄观里偷吃了镇元大仙的人参果！",
        "观音：啊！有这等事？真是岂有此理！",
        "红孩儿：他…他们还掀翻了镇元大仙的人参果树！",
        "观音：我不要活啦！你下次汇报工作的时候能否把重要的事情排在前面？",
        "红孩儿：哦。",
        "观音：不必担心，只要我这圣水一落地，枯木也可以回春。",
        "「滴答」",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "【神话】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob, pob;
        string msg;
        mapping my, ips;
        string ip, *ks;

        ips = ([ ]);
        /*
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) && 
                                                 !query("env/no_story", $1) && 
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        */

        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !query("born", pob) || 
                    ! living(pob) || ! environment(pob) ||
                    !query("outdoors", environment(pob)) || 
                    pob->is_ghost() ||
                    query("env/no_story", pob) || 
                    query("doing", pob) || 
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (! sizeof(ips))
                return 0;

        // 随即抽一个IP
        ks = keys(ips);
        ip = ks[random(sizeof(ks))];

        // 在该IP地址上随即抽取一个玩家
        ob = ips[ip][random(sizeof(ips[ip]))];
        
        if( query("gift/water", ob)>4 || random(5) )
        {
                msg = HIW "只见" + ob->name(1) +
                      HIW "全身白芒闪耀，神采奕奕，似乎没有起到什么作用。" NOR;
 
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                my["food"]   = ob->max_food_capacity();
                my["water"]  = ob->max_water_capacity();
        } else
        {
                msg = HIC "霎那间" + ob->name(1) +
                      HIC "全身被紫芒笼罩，灵台间光华闪烁，如获重生。" NOR;
                addn("int", 1, ob);
                addn("gift/water", 1, ob);
        }
        return msg;
}
