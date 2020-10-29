// /adm/daemons/faction.c 随机NPC技能管理守护程序
// By Alf, Last Update 2003.0722
// 目前可供杀手及护院调用

#include <ansi.h>
#include "include/faction.h"

public mapping *query_all_skill();              //返回所有技能情况列表
public int show_skill(object me, string arg);   //查询可设定技能的情况
public void gen_npc(object me, string arg);     //逐步设定各项人物数据
public void ran_skill(object me, string arg);   //从列表中指定或随机选定某种技能
public void gen_skill(object me);               //根据选定的参数设定各项武功技能
public void gen_dbase(object me);               //设定性别民族精气内力等各项数据
public void gen_items(object me);               //生成武器护甲马匹等各项携带物品

//返回所有技能情况列表
public mapping *query_all_skill()
{
    return all_skill;
}

//查询可设定技能情况
public int show_skill(object me, string arg)
{
    int i, j;
    string gen, msg;

    if(!arg || arg == "")   //无参数显示全部
    {
        msg  = HIC "\n当前可供选择的技能有：\n" NOR;
        msg += HIG "----------------------------------------------------\n" NOR;
        j = sizeof(all_skill);
        for(i = 0; i < j; i++)
        {
            if(all_skill[i]["no_list"])
            {
                j -= 1;
                continue;
            }
            if(!weapon_type[all_skill[i]["weapon"]])
                weapon_type[all_skill[i]["weapon"]] = "武功";
            msg += sprintf(HIW "名称：" HIY "%-12s" NOR
                           HIW "门派：" HIG "%-8s" NOR
                           HIW "类型：" HIC"%-6s" NOR
                           HIW "马术：" HIB"%-4s\n" NOR,
                           all_skill[i]["name"],
                           all_skill[i]["faction"],
                           weapon_type[all_skill[i]["weapon"]],
                           all_skill[i]["horse"] ? HIG "是" : "否");
        }
        msg += HIG "----------------------------------------------------\n" NOR;
        msg += HIC "共有 "HIW + chinese_number(j) + HIC" 种技能可供选择。\n\n" NOR;
    }
    else
        if(arg) //按照参数查询并显示
    {
        for(i = 0; i < sizeof(all_skill); i++)
        {
            if(all_skill[i]["code"] == arg || all_skill[i]["name"] == arg)
            {
                me->set_temp("query_faction", arg);
                if(!weapon_type[all_skill[i]["weapon"]])
                    weapon_type[all_skill[i]["weapon"]] = "武功";
                msg = sprintf(HIW "\n「" HIY "%s" HIW "」是" HIC "%s"
                              HIW "的一种%s", all_skill[i]["name"],
                                              all_skill[i]["faction"],
                                              weapon_type[all_skill[i]["weapon"]]);

                if(all_skill[i]["gender"] == "all")
                    msg += "，不限使用对象";
                else
                {
                    if(all_skill[i]["gender"] == "male")
                        gen = "男性";
                    if(all_skill[i]["gender"] == "female")
                        gen = "女性";
                    msg += "，仅限"HIG + gen + HIW"使用";
                }
                if(all_skill[i]["horse"] == 1)
                    msg += "，需要骑马方能尽情施展。\n" NOR;
                else
                    msg += "，无须骑马便可尽情施展。\n" NOR;
                break;
            }
            else
                msg = "";

        }
        if(msg == "")
            msg += YEL "目前尚未有这种技能供选择。\n" NOR;
    }

    me->start_more(msg);
    return 1;
}

//逐步设定各项人物数据
public void gen_npc(object me, string arg)
{
    ran_skill(me, arg);
    gen_skill(me);
    gen_dbase(me);
    gen_items(me);
    return;
}

//从列表中指定或随机选定某种技能
public void ran_skill(object me, string arg)
{
    int i;
    string *key;
    mapping skill = ([]);

    if(!arg)    //无参数随机选择一种
    {
        for(i = 0; i < sizeof(all_skill); i++)
        {
            if(all_skill[i]["no_list"]) //特殊种类不列入随机选择之中
                continue;
            if(me->query("gender") == "男性"
                && all_skill[i]["gender"] == "female")  //预防姓名与性别不太相符
                    continue;
            if(me->query("gender") == "女性"
                && all_skill[i]["gender"] == "male")  //预防姓名与性别不太相符
                    continue;
            skill += ([ all_skill[i]["code"] : all_skill[i]["name"], ]);
        }
        key = sort_array(keys(skill), 1);
        arg = key[random(sizeof(key))];
    }

    for(i = 0; i < sizeof(all_skill); i++)
    {
        if(all_skill[i]["name"] == arg
            || all_skill[i]["code"] == arg) //按照参数查询并选择
        {
            skill = all_skill[i];
            me->set("generation_skill", skill);
            break;
        }
    }

    return;
}

//根据选定的参数设定各项武功技能
public void gen_skill(object me)
{
    int i, level;
    mapping skill, m_skill, p_skill, special;
    string *key;

//删除原有技能
    skill = me->query_skill_prepare();
    if(!skill)
        skill = ([]);

    if(mapp(skill) && sizeof(skill) > 0)
    {
        key = keys(skill);
        for(i = 0; i < sizeof(key); i++)
        {
            me->prepare_skill(key[i]);
        }
    }

    skill = me->query_skills();
    if(mapp(skill) && sizeof(skill) > 0)
    {
        key = keys(skill);
        for(i = 0; i < sizeof(key); i++)
        {
            me->map_skill(key[i]);
            map_delete(me->query_skills(), key[i]);
        }
    }

    special = me->query("generation_skill/special");
    if(mapp(special) && sizeof(special) > 0)
    {
        key = keys(special);
        for(i = 0; i < sizeof(key); i++)
        {
            me->delete(key[i]);
        }
    }

//设定新增技能
    skill = me->query("generation_skill");
    level = me->query("set_skill/level");
    if(!level)
        level = 250;
    if(level > 900)
        level = 900;

    if(mapp(skill) && sizeof(skill) > 0)
    {
        m_skill = me->query("generation_skill/m_skill");
        if(mapp(m_skill) && sizeof(m_skill) > 0)
        {
            key = keys(m_skill);
            for(i = 0; i < sizeof(m_skill); i++)
            {
                me->set_skill(key[i], level);
                me->set_skill(m_skill[key[i]], level);
                me->map_skill(key[i], m_skill[key[i]]);
            }
        }

        p_skill = me->query("generation_skill/p_skill");
        if(mapp(p_skill) && sizeof(p_skill) > 0)
        {
            key = keys(p_skill);
            for(i = 0; i < sizeof(p_skill); i++)
            {
                me->prepare_skill(key[i], p_skill[key[i]]);
            }
        }

        special = me->query("generation_skill/special");
        if(mapp(special) && sizeof(special) > 0)
        {
            key = keys(special);
            for(i = 0; i < sizeof(key); i++)
            {
                me->set(key[i], special[key[i]]);
            }
        }
    }
    me->reset_action();
    return;
}

//设定性别民族精气内力等各项数据
public void gen_dbase(object me)
{
    int level = me->query("set_skill/level");
    string gender = me->query("generation_skill/gender");
    string weapon = me->query("generation_skill/weapon");
    string *gends = ({ "男性", "女性", });
    string *nation = ({ "汉族", "满族", });

    if(!me->query("generation_skill"))
        return;

    if(!gender || gender == "all")
    {
        if(me->query("gender"))
            me->set("gender", me->query("gender"));
        else
            me->set("gender", gends[random(sizeof(gends))]);
    }
    else
        if(gender == "male")
            me->set("gender", "男性");
    else
        if(gender == "female")
            me->set("gender", "女性");
    else
        me->set("gender", "男性");

    if(me->query("generation_skill/nation"))
        me->set("nation", me->query("generation_skill/nation"));
    else
        me->set("nation", nation[random(sizeof(nation))]);

    if(!level)
        level = 250;
    if(level > 900)
        level = 900;

    if(me->is_house_huyuan())   //护院的计算公式
    {
        me->set("qi", level*15);
        me->set("max_qi", level*15);
        me->set("eff_qi", level*15);
        me->set("jing", level*12);
        me->set("eff_jing", level*12);
        me->set("max_jing", level*12);
        me->set("jingli", level*18);
        me->set("max_jingli", level*18);
        me->set("neili", level*20);
        me->set("max_neili", level*20);
        me->set("jiali", level/4);
        me->set("combat_exp", (level/10)*level*level);
        me->set("set_skill/level", level);
    }
    else
        if(me->is_killer())    //杀手的计算公式
    {

        if(weapon == "unarmed"
            || weapon == "claw"
            || weapon == "finger")
                level = level*10/9;   //空手技能等级略高
        me->set("qi", level*5);
        me->set("max_qi", level*5);
        me->set("eff_qi", level*5);
        me->set("jing", level*4);
        me->set("eff_jing", level*4);
        me->set("max_jing", level*4);
        me->set("jingli", level*4);
        me->set("max_jingli", level*4);
        me->set("neili", level*10);
        me->set("max_neili", level*10);
        me->set("combat_exp", (level/10)*level*level);
        me->set("set_skill/level", level);
    }
    else    //默认的计算公式
    {
        me->set("qi", level*5);
        me->set("max_qi", level*5);
        me->set("eff_qi", level*5);
        me->set("jing", level*4);
        me->set("eff_jing", level*4);
        me->set("max_jing", level*4);
        me->set("jingli", level*4);
        me->set("max_jingli", level*4);
        me->set("neili", level*10);
        me->set("max_neili", level*10);
        me->set("combat_exp", (level/10)*level*level);
        me->set("set_skill/level", level);
    }

    return;
}

//生成武器护甲马匹等各项携带物品
public void gen_items(object me)
{
    int i;
    string my_weapon, file;
    object *inv, weapon, armor, horse;

    if(!me->query("generation_skill"))
        return;

    if(me->query("carry_obj"))  //删除旧的携带物品列表
        me->delete("carry_obj");

    inv = all_inventory(me);
    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_autoload())
            continue;
        destruct(inv[i]);   //摧毁原有携带物品
    }

    my_weapon = me->query("generation_skill/weapon");
    if(my_weapon != "unarmed"
        && my_weapon != "claw"
        && my_weapon != "finger")   //兵刃技能穿布衣携武器
    {
        if(me->query("generation_skill/code") == "xiyang")
            armor = new("/clone/misc/xifu");    //洋鬼子穿西服
        else
            armor  = new("/clone/misc/cloth");
        weapon = new(weapon_file[my_weapon]);
        file = base_name(weapon);
        me->set("carry_obj/weapon", file);
        if(me->query("generation_skill/code") != "xiyang")
            "/adm/daemons/x_named"->x_name(weapon, "");
        weapon->move(me);
        weapon->wield();
    }
    else    //空手技能穿护甲
    {
        armor = new("/clone/misc/ruankai");
    }
    file = base_name(armor);
    me->set("carry_obj/armor", file);
    armor->move(me);
    armor->wear();

    if(me->query("generation_skill/horse") == 1)    //马战技能骑马
    {
        horse = new("/clone/horse/huangbiao-ma");
        file = base_name(horse);
        me->set("carry_obj/horse", file);
        horse->move(me);
        horse->ride();
    }
    return;
}
