// story:feng 凤舞

#include <ansi.h>

mixed random_gift();

inherit F_CLEAN_UP;

nosave mixed *story = ({
        "路人：这位大哥，这附近最近有什么奇怪的事情发生吗？",
        "樵夫：听说最近东边的湖畔经常会飞来一只凤凰。",
        "路人：原来真有这事....",
        "樵夫：唉！又是个来送死的。",
        "路人：听说上回老五看到了凤凰起舞，结果身法大涨，现在寻常人都打不过他了。",
        "......",
        "湖边，凤凰看着水中的倒影，陶醉在自己的美丽中，翩翩起舞。",
        "周围随着凤舞刮起了旋风。",
        "呼～～～～",
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
        mapping ips;
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

        if( query("gift/feng", ob)>4 || random(5) )
        {
                msg = HIR + ob->name(1) + "被一阵旋风刮起，重重摔在了地上。" NOR;
                if( query("combat_exp", ob)<1000000 || 
                    query("qi", ob)<1000 )
                        ob->unconcious();
                else
                {
                        set("qi", 10, ob);
                        set("eff_qi", 10, ob);
                        set("jing", 1, ob);
                        set("eff_jing", 1, ob);
                }
        } else
        {
                msg = HIG "听说" + ob->name(1) +
                      HIG "无意中看到了凤凰起舞。" NOR;
                addn("dex", 1, ob);
                addn("gift/feng", 1, ob);
        }
        return msg;
}

