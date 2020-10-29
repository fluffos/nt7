// /adm/npc/bunong.c 玩家住宅负责人：布侬
// By Alf, Last Update 2003.0730
// Modify By Alf@Syzf, Last Update 2005.0402
// 增加原址改建及贵宾扩限功能

#include <ansi.h>
#include "house_picture.h"

inherit NPC;

#define BASE_DIR    "/clone/house/base/"
#define VIP_VALUE   1000
#define VIP_LIMIT   28
#define VIP_ORIGIN  12

public int show_type(object me);                        //房型列表
public int show_base(object me);                        //地块列表
private int choice_type(string arg);                    //选定房型
private int choice_base(string arg);                    //选定地块
private int build_house(string arg);                    //建造房屋
private int do_rebuild(string arg);                     //原址改建
private int do_cession(string arg);                     //房产转让
private int do_dismantle(string arg);                   //房屋拆除
public void confirm_type(string yn);                    //确认选型
public void confirm_base(string yn);                    //确认选地
public void confirm_build(string yn);                   //确认建造
public void confirm_rebuild(string yn);                 //确认改建
public void confirm_cession(string yn);                 //确认转让
public void confirm_dismantle(string yn);               //确认拆除
public void confirm_addvips(string yn);                 //确认扩限
public void check_password(string passwd, object me);   //密码检测
public void add_all_inquiry();                          //查询主题
private int ask_cmds();                                 //指令帮助
private int house_picture_user();                       //显示图样
private int house_picture_bang();                       //显示图样
private int house_picture_xian();                       //显示图样
private void reset_all_static();                        //变量清零
private int add_vip_count(string arg);                  //贵宾扩限

static int the_value = 0;
static int max_laodu = 0;
static string the_name = "";
static string the_type = "";
static string the_base = "";
static mapping npc_data = ([]);

void create()
{
    set_name("布侬", ({ "bu nong", "bu", "nong" }));
    set("nickname", HIC"居有其屋"NOR);
    set("title", HIM"建筑精灵"NOR);
    set("channel_id", "建筑精灵");
    set("gender", "女性");
    set("shen", 0);
    set("age", 20);
    set("per", 40);
    set("no_get", 1);
    set("wiz_tester", 1);
    set("combat_exp", 10000000);
    set("attitude", "friendly");
    set("long", "\n这是一个年轻的女孩子，却一手操纵了「"HIY +
                MUD_NAME + NOR"」的所有房屋建筑事宜。\n");

    setup();
    carry_object("/clone/misc/cloth")->wear();
    add_all_inquiry();
}

void init()
{
    add_action("show_type", "showtype");              //房型列表
    add_action("choice_type", "choosetype");          //选定房型
    add_action("show_base", "showbase");              //地块列表
    add_action("choice_base", "choosebase");          //选定地块
    add_action("build_house", "buildhouse");          //建造房屋
    add_action("do_cession", "cession");              //房产转让
    add_action("do_dismantle", "dismantle");          //房屋拆除
    add_action("do_rebuild", "rebuild");              //原地改建
    add_action("add_vip_count", "addvips");           //贵宾加量
}

public void add_all_inquiry()
{
    int i;
    string type;
    mapping *all_house, all_inquiry;

    all_inquiry = ([]);
    all_house   = HOUSE_D->query_house_type();
    for(i = 0; i < sizeof(all_house); i++)
    {
        if(all_house[i]["type"] == "user")
        {
            type = "玩家住宅";
            all_inquiry += ([ all_house[i]["name"] : (: house_picture_user :)]);
            all_inquiry += ([ type : (: house_picture_user :)]);
        }
        if(all_house[i]["type"] == "bang")
        {
            type = "帮会驻地";
            all_inquiry += ([ all_house[i]["name"] : (: house_picture_bang :)]);
            all_inquiry += ([ type : (: house_picture_bang :)]);
        }
        if(all_house[i]["type"] == "xian")
        {
            type = "散仙居所";
            all_inquiry += ([ all_house[i]["name"] : (: house_picture_xian :)]);
            all_inquiry += ([ type : (: house_picture_xian :)]);
        }
    }

    all_inquiry += ([
        "指令" : (: ask_cmds :),
        "帮助" : (: ask_cmds :),
        "cmds" : (: ask_cmds :),
        "help" : (: ask_cmds :),
    ]);

    this_object()->set("inquiry", all_inquiry);
}

private int ask_cmds()
{
    object me, ob;
    me = this_player();
    ob = this_object();

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, HIW@TEXT

        房型列表：showtype
        地块列表：showbase
        选定房型：choosetype <屋宅名称>
        选定地块：choosebase <地块名称>
        建造房屋：buildhouse <屋宅名称> on <地块名称>
        贵宾扩限：   addvips <屋宅名称>
        原址改建：   rebuild <原有屋宅名称>     （需验证原有屋宅编码）
        房产转让：   cession <屋宅名称> to <对方ID> （需验证屋宅编码）
        房屋拆除： dismantle <你的ID> <屋宅名称>    （需验证屋宅编码）

TEXT NOR);
    return 1;
}

public int show_type(object me)
{
    object ob;

    me = this_player();
    ob = this_object();

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "说了几句话。\n", environment(me), ({ me, ob }));
    HOUSE_D->show_type(me);
    return 1;
}

private int choice_type(string arg)
{
    int i, value;
    object me, ob;
    mapping *house_type;
    string name, type;

    me = this_player();
    ob = this_object();

    if(!arg || arg == "")
        return notify_fail(HIW "指令格式：choosetype <屋宅名称>\n" NOR);

    house_type = HOUSE_D->query_house_type();
    for(i = 0; i < sizeof(house_type); i++)
    {
        if(arg != house_type[i]["name"])
            continue;
        type  = house_type[i]["type"];
        name  = house_type[i]["name"];
        value = house_type[i]["value"];
    }

    if(!type)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：目前并无「"
                        HIW + arg + NOR YEL"」供建造，请仔细查看"
                            "屋宅类型(showtype)。\n" NOR);
        return 1;
    }

    if(type == "xian")
    {
        if(!wizardp(me) && wizhood(me) != "(immortal)")
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下还没有位列"
                                "上界仙班，不能建造「" HIW + name + NOR
                            YEL "」这种屋宅。\n" NOR);
            return 1;
        }
    }

    if(type == "bang")
    {
        if(!wizardp(me) && me->query("bang/class") != 1)
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下尚未荣登"
                                "帮主宝座，不能建造「" HIW + name + NOR
                            YEL "」这种屋宅。\n" NOR);
            return 1;
        }

        if(me->query("bank/gold") < value)
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下的存款不够"
                                "支付「"HIW + name + NOR YEL"」这种屋宅"
                                "的造价，去存够了钱再来吧。\n" NOR);
            return 1;
        }

        if(!wizardp(me) && wizhood(me) != "(player)")
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下业已脱胎"
                                "升仙，不用再追求这些凡俗之物了。\n" NOR);
            return 1;
        }
    }

    if(type == "user")
    {
        if(me->query("house/user")
            && !me->query_temp("building_house/rebuild"))   //并非改建
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下已经拥有一套"
                                "玩家住宅了，不能再多造。\n" NOR);
            tell_object(me, YEL + ob->name(1) + "又笑道：如果想在原址改建，"
                            "请使用" HIW " rebuild " NOR YEL "指令。\n" NOR);
            return 1;
        }

        if(me->query("bank/gold") < value)
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下的存款不够"
                                "支付「"HIW + name + NOR YEL"」这种屋宅"
                                "的造价，去存够了钱再来吧。\n" NOR);
            return 1;
        }

        if(!wizardp(me) && wizhood(me) != "(player)")
        {
            message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, YEL + ob->name(1) + "摇头道：阁下业已脱胎"
                                "升仙，不用再追求这类凡俗之物了。\n" NOR);
            return 1;
        }
    }
    message("vision", ob->name(1) + "点了点头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, HIC "\n" + ob->name(1) + "点头道：" NOR);
    HOUSE_D->choice_type(arg, me);
    tell_object(me, HIC "，确定吗(y/n)？\n" NOR);
	input_to("confirm_type", me);
    return 1;
}

public void confirm_type(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        me->delete_temp("building_house");
        message_vision(YEL "$N想了想，对$n摇头道：我还是再看看吧。\n" NOR, me, ob);
        return;
    }
    else
        message_vision(HIC "$N想了想，对$n点头道：我就选择这一种。\n" NOR, me, ob);
    return;
}

public int show_base(object me)
{
    object ob;

    me = this_player();
    ob = this_object();

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "说了几句话。\n", environment(me), ({ me, ob }));
    HOUSE_D->show_base(me);
    return 1;
}

private int choice_base(string arg)
{
    int i;
    object me, ob, room;
    string name, type;
    mapping base;

    me = this_player();
    ob = this_object();
    base = HOUSE_D->query_house_base();

    if(!arg || arg == "")
        return notify_fail(HIW "指令格式：choosebase <地块名称>\n" NOR);

    if(!me->query_temp("building_house"))
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：请先选择好你想要"
                            "建造的屋宅类型(choosetype)。\n" NOR);
        return 1;
    }

    name = me->query_temp("building_house/name");
    type = me->query_temp("building_house/type");
    for(i = 0; i < sizeof(base); i++)
    {
        if(base[i]["name"] == arg)
        {
            room = get_object(BASE_DIR + base[i]["file"]);
            if(base[i]["type"] != type)
            {
                message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, YEL + ob->name(1) + "摇头道：「" HIW + arg +
                            NOR YEL "」不适合建造你所选择的「" HIC + name +
                            NOR YEL "」，请另选一处合适的地块。\n" NOR);
                return 1;
            }
            if(room->query("house_build") >= room->query("max_build"))
            {
                message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, YEL + ob->name(1) + "摇头道：「" HIW + arg +
                            NOR YEL "」那里已经造了足够多的屋宅，请重新选一处"
                                    "有空位的地块吧。\n" NOR);
                return 1;
            }
            message("vision", ob->name(1) + "点了点头，在" + me->name() +
                              "耳边小声说了几句话。\n", environment(me),
                                                        ({ me, ob }));
            tell_object(me, HIC "\n" + ob->name(1) + "点头道：" NOR);
            HOUSE_D->choice_base(arg, me);
            tell_object(me, HIC "，确定吗(y/n)？\n" NOR);
	        input_to("confirm_base", me);
            return 1;
        }
    }

    message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, YEL + ob->name(1) + "摇头道：没有「" HIW + arg +
                NOR YEL"」这个地块，请仔细查看地块列表(showbase)。\n" NOR);
    return 1;
}

public void confirm_base(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        me->delete_temp("building_house/base");
        message_vision(YEL "$N想了想，对$n摇头道：我还是再看看吧。\n" NOR, me, ob);
        return;
    }
    else
        message_vision(HIC "$N想了想，对$n点头道：我就选择这一处。\n" NOR, me, ob);
    return;
}

private int build_house(string arg)
{
    int value;
    object me, ob;
    mapping base;
    string name, type, target;

    me = this_player();
    ob = this_object();

    if(!arg || sscanf(arg, "%s on %s", type, target) != 2)
        return notify_fail(HIW "指令格式：buildhouse <屋宅类型> "
                               "on <地块名称>\n" NOR);

    name = me->query_temp("building_house/name");
    base = me->query_temp("building_house/base");
    if(!name)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                         "耳边小声说了几句话。\n", environment(me),
                                                   ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：阁下还没有选择好"
                            "要建造的屋宅类型。\n" NOR);
        return 1;
    }
    if(!base)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                         "耳边小声说了几句话。\n", environment(me),
                                                   ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：阁下还没有选择好"
                            "要建造屋宅的地块。\n" NOR);
        return 1;
    }
    if(type != name)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                         "耳边小声说了几句话。\n", environment(me),
                                                   ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：阁下刚才好象选择"
                            "的不是这种屋宅类型吧？\n" NOR);
        return 1;
    }
    if(target != base["name"])
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                         "耳边小声说了几句话。\n", environment(me),
                                                   ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：阁下刚才好象选择"
                            "的不是这个地块吧？\n" NOR);
        return 1;
    }

    value = me->query_temp("building_house/val_t"); //房屋的造价
    if(!me->query_temp("rebuild_house"))
        value += base["value"];                     //非改建需加宅基地价
    me->set_temp("building_house/value", value);    //屋宅总造价
    if(me->query("bank/gold") < value)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                         "耳边小声说了几句话。\n", environment(me),
                                                   ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：阁下的存款不够"
                            "支付屋宅的造价共计 "WHT + value + YEL
                            " 两黄金，去存够了钱再来吧。\n" NOR);
        return 1;
    }

    message("vision", ob->name(1) + "点了点头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, HIC + ob->name(1) + "点头道：你想在「"
                    HIW + target + HIC "」建造一套「"
                    HIW + name + HIC"」，费用需 "
                    HIY + value + " 两黄金"
                    HIC "，确定吗(y/n)？\n" NOR);
	input_to("confirm_build", me);
    return 1;
}

public void confirm_build(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        message_vision(YEL "$N想了想，对$n摇头道：等我再考虑一下吧。\n" NOR, me, ob);
        return;
    }
    message_vision(HIC "$N想了想，对$n点头道：就这样吧，我决定了。\n" NOR, me, ob);
    me->set_temp("building_house/zhuan", "HOUSE_D");    //附加屋宅来源标志
    me->set_temp("building_house/build", "build");      //附加建造标志以扣钱

    if(me->query_temp("rebuild_house")) //原址改建前先拆除旧有屋宅
    {
        HOUSE_D->do_dismantle(me, me->query_temp("building_house/rebuild"));
    }

    HOUSE_D->build_house(me);

    if(me->query_temp("rebuild_house"))
    {
        me->delete_temp("rebuild_house");   //标记删除，变量清零
        reset_all_static();
    }

    return;
}

private int do_rebuild(string arg)
{
    int i, vips;
    object me, ob, room, huyuan;
    string name, type, tag, *key, msg;
    mapping build, house, base, old_vip;

    if(!arg || arg == "")
        return notify_fail(HIW "指令格式：rebuild <原有屋宅名称>\n" NOR);

    me = this_player();
    ob = this_object();
    build = me->query("house/build");
    if(!build)
    {
        tell_object(me, YEL "你有建造过这种屋宅吗？\n" NOR);
        return 1;
    }
    if(mapp(build) && sizeof(build) > 0)
    {
        key = keys(build);
        for(i = 0; i < sizeof(key); i++)
        {
            if(build[key[i]] == arg)
            {
                house = me->query("house/" + key[i]);
                the_type = key[i];  //记录旧宅类型
                the_name = arg;     //记录旧宅名称
                break;
            }
        }
        if(!house)
        {
            tell_object(me, YEL "你有建造过这种屋宅吗？\n" NOR);
            return 1;
        }
    }
    if(mapp(house) && sizeof(house) > 0)
    {
        key = keys(house);
        for(i = 0; i < sizeof(key); i++)
        {
            if(key[i] == "base")
            {
                base = house[key[i]];
                me->set_temp("building_house/base", base);
                the_base = base["name"];   //记录宅基名称
                the_value = house["value"]; //记录旧宅价值
                room = get_object(house["entry"]);
                max_laodu = (int)room->query("max_laodu");   //大门牢度
                huyuan = get_object(room->query("huyuan"));    //查找护院
                huyuan->restore();
//------------------------------------------------------------------------------------
                npc_data["name"]   = huyuan->query("name");     //护院姓名
                npc_data["long"]   = huyuan->query("long");     //护院描述
                npc_data["gender"] = huyuan->query("gender");   //护院性别

                if(stringp(huyuan->query("nickname")))          //护院外号
                    npc_data["nickname"] = huyuan->query("nickname");
                if(stringp(huyuan->query("title")))             //护院头衔
                    npc_data["title"] = huyuan->query("title");

                npc_data["level"] = huyuan->query("set_skill/level");   //护院等级
                npc_data["skill"] = huyuan->query("generation_skill/code"); //护院技能

                vips = huyuan->query("vip_limit");
                if(vips <= 0)
                    vips = VIP_ORIGIN;
                npc_data["vip_limit"] = vips;       //贵宾上限

                old_vip = huyuan->query("vip");
                if(mapp(old_vip) && sizeof(old_vip) > 0)
                    npc_data["vip"] = old_vip;
//------------------------------------------------------------------------------------
                me->set_temp("building_house/rebuild", the_type);   //作上可改建标记
                break;
            }
        }
    }

    if(!me->query_temp("building_house/name"))
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：改建前请先选择好你想要"
                            "建造的屋宅类型(choosetype)。\n" NOR);
        return 1;
    }

    name = me->query_temp("building_house/name");
    type = me->query_temp("building_house/type");
    room = get_object(base["file"]);
    if(name == arg)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                          "耳边小声说了几句话。\n", environment(me),
                                                    ({ me, ob }));
        tell_object(me, sprintf(YEL "%s摇头道：你已经建造在「" HIW "%s" NOR
                                YEL "」上的屋宅不就是「" HIC "%s" NOR
                                YEL "」这种房型吗？\n" NOR,
                                ob->name(1), base["name"], name));
        return 1;
    }
    if(room->query("can_build") != type)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                          "耳边小声说了几句话。\n", environment(me),
                                                    ({ me, ob }));
        tell_object(me, sprintf(YEL "%s摇头道：你原有的宅基「" HIW "%s" NOR
                                YEL "」不适合建造你选择改建的「" HIC "%s" NOR
                                YEL "」，请另选合适的房型。\n" NOR,
                                    ob->name(1), base["name"], name));
        return 1;
    }
/*
//-------------------------------------------------------------------------------
    tell_object(me, sprintf("\n\n\t旧宅名称：%s\n"
                            "\t旧宅类型：%s\n"
                            "\t旧宅地基：%s\n"
                            "\t旧宅价值：%d\n"
                            "\t大门牢度：%d\n",
                            the_name, the_type, the_base, the_value, max_laodu));
    msg = "";
    key = sort_array(keys(npc_data), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        if(stringp(npc_data[key[i]]))
            msg += sprintf("\t%s : %s\n", key[i], npc_data[key[i]]);
        if(intp(npc_data[key[i]]))
            msg += sprintf("\t%s : %d\n", key[i], npc_data[key[i]]);
        if(mapp(npc_data[key[i]]))
            msg += sprintf("\t%s : %d\n", key[i], sizeof(npc_data[key[i]]));
    }
    msg += "\n";
    tell_object(me, msg);
//-------------------------------------------------------------------------------
*/
    message("vision", ob->name(1) + "点了点头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me),
                                                ({ me, ob }));
    tell_object(me, sprintf(HIC "\n%s点头道：你打算改建在「" HIW "%s"
                            HIC "」上所拥有的「" HIY "%s"
                            HIC "」，确定吗(y/n)？\n" NOR,
                                ob->name(1), base["name"], the_name));

    input_to("confirm_rebuild", me);
    return 1;
}

public void confirm_rebuild(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        reset_all_static();
        message_vision(YEL "$N想了想，对$n摇头道：等我再考虑一下吧。\n" NOR, me, ob);
        return;
    }
    message_vision(HIC "$N想了想，对$n点头道：就这样吧，我决定了。\n" NOR, me, ob);
//--------------------------------------------------------------------
    me->set_temp("rebuild_house/the_base", the_base);   //记录旧宅地基
    me->set_temp("rebuild_house/the_name", the_name);   //记录旧宅名称
    me->set_temp("rebuild_house/the_type", the_type);   //记录旧宅类型
    me->set_temp("rebuild_house/the_value", the_value); //记录旧宅价值
    me->set_temp("rebuild_house/max_laodu", max_laodu); //记录大门牢度
    me->set_temp("rebuild_house/npc_data", npc_data);   //记录护院数据
//--------------------------------------------------------------------
    tell_object(me, HIW "请输入原有屋宅编码：" NOR);
    input_to("check_password", 1, me);
    return;
}

private int do_cession(string arg)
{
    int i;
    object me, who, ob;
    string target, name, *key;
    mapping build;

    me = this_player();
    ob = this_object();

    if(!arg || sscanf(arg, "%s to %s", name, target) != 2)
        return notify_fail(HIW "指令格式：cession <屋宅名称> "
                               "to <被转让者ID>\n" NOR);

    build = me->query("house/build");
    if(sizeof(build) == 0)
        return notify_fail(YEL "你有建造过屋宅吗？\n" NOR);

    key = sort_array(keys(build), 1);
    if(target == me->query("id"))
        return notify_fail(YEL "转让给自己？搞错了吧。\n" NOR);

    if(!objectp(who = present(target, environment(me)))
        || !userp(who)
        || !interactive(who)
        || !who->is_livings())
            return notify_fail(YEL "这里没有这个人。\n" NOR);

    for(i = 0; i < sizeof(key); i++)
    {
        if(build[key[i]] != name)
            continue;
        if(build[key[i]] == name)
        {
            if(key[i] == "bang" || key[i] == "xian")
            {
                if(!wizardp(me))
                {
                    message("vision", ob->name(1) + "摇了摇头，在"
                                    + me->name() + "耳边小声说了几句话。\n",
                                            environment(me), ({ me, ob }));
                    tell_object(me, YEL + ob->name(1) + "摇头道：「"
                                    HIW + name + NOR YEL"」这种屋宅"
                                        "是不可以转让的。\n" NOR);
                    return 1;
                }

                message("vision", ob->name(1) + "点了点头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, HIC + ob->name(1) + "点头道：你所拥有的「"
                                HIY + name + HIC "」将被转让给『"
                                HIW + who->name() +
                                HIC "』，确定吗(y/n)？\n" NOR);
                me->set_temp("cession_house/type", key[i]);
                me->set_temp("cession_house/name", who->query("id"));
                input_to("confirm_cession", me);
                return 1;
            }

            if(key[i] == "user")
            {
                if(!wizardp(me) && wizhood(who) != "(player)")
                {
                    message("vision", ob->name(1) + "摇了摇头，在"
                                    + me->name() + "耳边小声说了几句话。\n",
                                            environment(me), ({ me, ob }));
                    tell_object(me, YEL + "\n" + ob->name(1) + "摇头道："
                                        + who->name() + "已经不再需要"
                                        "这些凡俗事物了。\n" NOR);
                    return 1;
                }
                message("vision", ob->name(1) + "点了点头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, HIC + ob->name(1) + "点头道：你所拥有的「"
                                HIY + name + HIC "」将被转让给『"
                                HIW + who->name() +
                                HIC "』，确定吗(y/n)？\n" NOR);
                me->set_temp("cession_house/type", key[i]);
                me->set_temp("cession_house/name", who->query("id"));
                input_to("confirm_cession", me);
                return 1;
            }
        }
    }

    message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, YEL + "\n" + ob->name(1) + "摇头道：你有建造过「"
                    HIW + name + NOR YEL"」这种屋宅吗？\n" NOR);
    return 1;
}

public void confirm_cession(string yn)
{
    object me, ob;

    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        message_vision(YEL "$N想了想，对$n摇头道：等我再考虑一下吧。\n" NOR, me, ob);
        me->delete_temp("cession_house");
        return;
    }

    message_vision(HIC "$N想了想，对$n点头道：就这样吧，我决定了。\n" NOR, me, ob);
    tell_object(me, HIW "请输入屋宅编码：" NOR);
    input_to("check_password", 1, me);
    return;
}

private int do_dismantle(string arg)
{
    int i;
    object me, ob;
    string who, name, *key;
    mapping build;

    me = this_player();
    ob = this_object();

    if(!arg || sscanf(arg, "%s %s", who, name) != 2)
        return notify_fail(HIW "指令格式：dismantle <你的ID> <屋宅类型>\n" NOR);

    build = me->query("house/build");
    if(sizeof(build) == 0)
        return notify_fail(YEL "你有建造过屋宅吗？\n" NOR);

    if(who != me->query("id"))
        return notify_fail(YEL "你只能拆除自己所拥有的屋宅。\n" NOR);

    key   = sort_array(keys(build), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        if(build[key[i]] != name)
            continue;
        if(build[key[i]] == name)
        {
            if(key[i] == "bang" || key[i] == "xian")
            {
                if(!wizardp(me))
                {
                    message("vision", ob->name(1) + "摇了摇头，在"
                                    + me->name() + "耳边小声说了几句话。\n",
                                            environment(me), ({ me, ob }));
                    tell_object(me, YEL + ob->name(1) + "摇头道：「"
                                    HIW + name + NOR YEL"」这种屋宅"
                                        "是不可以拆除的。\n" NOR);
                    return 1;
                }
                message("vision", ob->name(1) + "点了点头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, HIC + ob->name(1) + "点头道：你所拥有的「"
                                HIY + name + HIC "」将被拆除，"
                                    "确定吗(y/n)？\n" NOR);
               me->set_temp("dismantle_house", key[i]);
                input_to("confirm_dismantle", me);
                return 1;
            }

            if(key[i] == "user")
            {
                message("vision", ob->name(1) + "点了点头，在" + me->name() +
                                  "耳边小声说了几句话。\n", environment(me),
                                                            ({ me, ob }));
                tell_object(me, HIC + ob->name(1) + "点头道：你所拥有的「"
                                HIY + name + HIC "」将被拆除，"
                                    "确定吗(y/n)？\n" NOR);
	            me->set_temp("dismantle_house", key[i]);
	            input_to("confirm_dismantle", me);
                return 1;
            }
        }
    }

    message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, YEL + "\n" + ob->name(1) + "摇头道：你有建造过「"
                    HIW + name + NOR YEL"」这种屋宅吗？\n" NOR);
    return 1;
}

public void confirm_dismantle(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        message_vision(YEL "$N想了想，对$n摇头道：等我再考虑一下吧。\n" NOR, me, ob);
        me->delete_temp("dismantle_house");
        return;
    }
    message_vision(HIC "$N想了想，对$n点头道：就这样吧，我决定了。\n" NOR, me, ob);
    tell_object(me, HIW "请输入屋宅编码：" NOR);
    input_to("check_password", 1, me);
    return;
}

public void check_password(string passwd, object me)
{
    object ob, who;
    string pass, type, arg;
    mapping house, temp;

    if(me->query_temp("cession_house/type"))
    {
        type = me->query_temp("cession_house/type");
    }
    else
        if(me->query_temp("dismantle_house"))
    {
        type = me->query_temp("dismantle_house");
    }
    else
        if(me->query_temp("rebuild_house/the_type"))
    {
        type = me->query_temp("rebuild_house/the_type");
    }
    else
    {
        tell_object(me, "类型不明，检测中止。\n");
        return;
    }

    house = me->query("house/" + type);
    pass = house["pass"];
    if(passwd != pass)
    {
        tell_object(me, HIR "密码错误！\n" NOR);
        reset_all_static();
        return;
    }

    ob = this_object();
    if(me->query_temp("cession_house"))
    {
       temp = me->query_temp("cession_house");
        arg  = temp["type"];

        tell_object(me, HIG "密码正确，开始转让......\n\n" NOR);
        if(!objectp(who = present(temp["name"], environment(me)))
            || !userp(who)
            || !interactive(who)
            || !who->is_livings())
        {
            tell_object(me, YEL "转让失败，这里没有这个人。\n" NOR);
            return;
        }

        HOUSE_D->do_cession(me, who, arg);
        me->delete_temp("cession_house");
        return;
    }
    else
        if(me->query_temp("dismantle_house"))
    {
        arg = me->query_temp("dismantle_house");
        tell_object(me, HIG "密码正确，开始拆除......\n\n" NOR);
        HOUSE_D->do_dismantle(me, arg);
        me->delete_temp("dismantle_house");
        return;
    }
    else
        if(me->query_temp("rebuild_house"))
    {
        tell_object(me, HIG "密码正确，开始改建......\n\n" NOR);
        build_house(sprintf("%s on %s",
                        me->query_temp("building_house/name"), the_base));
        return;
    }
    else
    {
        tell_object(me, "类型不明，操作中止。\n");
        return;
    }
}

private void reset_all_static()
{
    the_value = 0;
    max_laodu = 0;
    the_base = "";
    the_name = "";
    the_type = "";
    npc_data = ([]);
}

private int add_vip_count(string arg)
{
    int i, how;
    object me, ob, room, huyuan;
    mapping build, house;
    string *key, msg;

    if(!arg || arg == "")
        return notify_fail(HIW "指令格式：addvips <屋宅名称>\n" NOR);

    me = this_player();
    ob = this_object();
    build = me->query("house/build");
    if(!build)
    {
        tell_object(me, YEL "你有建造过这种屋宅吗？\n" NOR);
        return 1;
    }
    if(mapp(build) && sizeof(build) > 0)
    {
        key = keys(build);
        for(i = 0; i < sizeof(key); i++)
        {
            if(build[key[i]] == arg)
            {
                house = me->query("house/" + key[i]);
                me->set_temp("house_addvips/type", key[i]);
                break;
            }
        }
        if(!house)
        {
            tell_object(me, YEL "你有建造过这种屋宅吗？\n" NOR);
            return 1;
        }
    }
    if(mapp(house) && sizeof(house) > 0)
    {
        room = get_object(house["entry"]);
        huyuan = get_object(room->query("huyuan"));    //查找护院
        huyuan->restore();
        how = huyuan->query("vip_limit");
        if((int)how <= 0)
            how = VIP_ORIGIN;
    }

    if(how >= VIP_LIMIT)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                            "耳边小声说了几句话。\n", environment(me),
                                                    ({ me, ob }));
        tell_object(me, sprintf(YEL "\n%s摇头道：你的「%s」当前的贵宾限额"
                                    "已达%s位，无法再扩充了。\n" NOR,
                                        ob->name(1), arg, chinese_number(how)));
        return 1;
    }

    if(me->query("bank/gold") < VIP_VALUE)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                            "耳边小声说了几句话。\n", environment(me),
                                                    ({ me, ob }));
        tell_object(me, sprintf(YEL "\n%s摇头道：阁下的存款不够支付扩充贵宾限额"
                                    "的费用，去存够%s两黄金再来吧。\n" NOR,
                                        ob->name(1), chinese_number(VIP_VALUE)));
        return 1;
    }

    message("vision", ob->name(1) + "点了点头，在" + me->name() +
                      "耳边小声说了几句话。\n", environment(me),
                                                ({ me, ob }));
    tell_object(me, sprintf(HIC "\n%s点头道：你的「%s」当前贵宾限额是 " HIW "%s"
                            HIC " 位，\n你想花费" HIY "%s"
                            HIC "两黄金将贵宾限额扩充到 "
                            HIG "%s" HIC " 位吗(y/n)？\n" NOR,
                                ob->name(1), arg,
                                chinese_number(how),
                                chinese_number(VIP_VALUE),
                                chinese_number(how + 1)));

    me->set_temp("house_addvips/huyuan", room->query("huyuan"));
    input_to("confirm_addvips", me);
    return 1;
}

public void confirm_addvips(string yn)
{
    object me, ob;
    me = this_player();
    ob = this_object();

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        me->delete_temp("house_addvips");
        message_vision(YEL "$N想了想，对$n摇头道：等我再考虑一下吧。\n" NOR, me, ob);
        return;
    }

    message_vision(HIC "$N想了想，对$n点头道：就这样吧，我决定了。\n" NOR, me, ob);
    HOUSE_D->add_vip_limit(VIP_VALUE, me, ob);
    return;
}
