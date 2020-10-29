// /adm/daemons/housed.c 住宅系统总控程序
// By Alf, Last Update 2003.0730
// Modify By Alf@Syzf, Last Update 2005.0402
// 增加原址改建及贵宾扩限功能

/*
 本程序目前供以下文件调用：
/cmds/adm/conhouse.c                            已建屋宅转归玩家指令
/cmds/arch/shenxian.c                           将玩家升为散仙的指令
/cmds/imm/home.c                                散仙直接返回居所指令
/cmds/bang/bchuanwei.c                          玩家帮会帮主传位指令
/cmds/bang/btuoli.c                             玩家脱离玩家帮会指令
/cmds/usr/checkhouse.c                          查看个人屋宅情况指令

/adm/npc/bunong.c                               负责具体屋宅事务的NPC

/inherit/room/house_base.c                      宅基地块模板文件
/inherit/room/house_door.c                      屋宅大门模板文件
/inherit/room/house_room.c                      屋宅房间模板文件
/inherit/char/huyuan.c                          屋宅护院模板文件

宅基地块存放目录：/clone/house/base/
具体文件应具参数：can_build                     可供建造屋宅类型
                  max_build                     最大可建屋宅数目

屋宅模板存放目录：/clone/house/type/类型/名称/  类型分user、bang、xian，名称可改
具体文件应具参数：
大门场景文件：set_exits                         与内宅接口的名称（散仙居所无此项）
              set_entry                         与内宅接口的文件（散仙居所无此项）
              forbid_exits                      与内宅接口的名称（散仙居所专用项）
                                                散仙居所大门另有专用的valid_leave
              huyuan                            屋宅护院文件路径
              max_laodu                         大门的最大牢固度
              now_laodu                         大门的当前牢固度
客厅场景文件：resource/water                    客厅所供茶水名称
所有场景文件：owner                             屋宅主人的ID（初始为OWNER，可不设）
              owner_name                        屋宅主人姓名（初始为某人，可不设）

已建屋宅存放目录：/clone/house/user/屋宅主人ID/
                  /clone/house/xian/屋宅主人ID/
                  /clone/house/bang/帮会的名称/

本程序必须关联到的文件：
/include/globals.h                              全局变量定义文件
/adm/daemons/updated.c                          系统更新守护程序
/adm/daemons/factiond.c                         技能设定守护程序
*/

inherit F_DBASE;
#include <ansi.h>
#include "include/banned_name.h"                                //载入禁用名字列表
#include "include/house_typez.h"                                //载入可建房型列表
#include "include/house_basez.h"                                //载入可用地块列表

#define CMD_RM      "/cmds/wiz/rm"
#define CMD_CP      "/cmds/wiz/cp"
#define HOUSE_DIR   "/clone/house/"
#define SOURCE_DIR  "/clone/house/type/"                        //屋宅模板目录
#define BASE_DIR    "/clone/house/base/"                        //宅基地块目录
#define VIP_ORIGIN  12                                          //初始贵宾上限

#define FACTION_D    "/adm/daemons/factiond"

void sys_info(string msg);                                      //系统信息提示
public mapping *query_house_type();                             //返回房型列表
public mapping *query_house_base();                             //返回地块列表
public int show_type(object me);                                //显示可建房型
public int choice_type(string arg, object me);                  //选择建造房型
public int show_base(object me);                                //显示可用地块
public int choice_base(string arg, object me);                  //选择建造地块
public int build_house(object me);                              //建造所选屋宅
public int do_cession(object me, object ob, string arg);        //转让所选屋宅
public int do_dismantle(object me, string arg);                 //拆除某处屋宅
public int do_dismantle_all(object me);                         //拆除所有屋宅
public int do_short(object me, string arg);                     //设定房间名称
public int do_long(object me);                                  //设定房间描述
public int do_item(object me, string arg);                      //设定房内物品
public int look_house_door(string arg, object me, object ob);   //查看大门状况
public int push_house_door(string arg, object me, object ob);   //推门进入屋内
public int jiagu_house_door(string arg, object me, object ob);  //加固大门牢度
public int break_house_door(string arg, object me, object ob);  //攻门试图闯入
public int add_guest(string arg, object me, object ob);         //维护贵宾列表
public int add_vip_limit(int value, object me, object ob);      //扩充贵宾上限
public int ask_guest(object me, object ob);                     //查询是否贵宾
public int invite_guest(object me, string arg);                 //邀请某人作客
public int modify_huyuan(string arg, object me, object ob);     //修改护院姓名
public int ask_huyuan_level(object me, object ob);              //查询护院等级
public int ask_huyuan_faction(object me, object ob);            //查询护院技能
public int shenji_huyuan(string arg, object me, object ob);     //提升护院等级
public int set_huyuan_skill(string arg, object me, object ob);  //设置护院技能
private int add_entry(object me, string arg);                   //增添地块入口
private int del_entry(object me, string arg);                   //删除地块入口
public int get_long(string msg, string arg, object me);         //编辑房间描述
public int no_dismantle(object me, object ob, string arg);      //不拆除只重设
public void confirm_setskill(string yn, object me, object ob);  //确认设定技能
public string random_generation_password(int passlen);          //随机产生密码

//设置程序在系统频道所用名字
void create()
{
    seteuid(ROOT_UID);
    set("channel_id", "房屋精灵");
}

//系统信息提示
void sys_info(string msg)
{
    CHANNEL_D->do_channel(this_object(), "sys", msg);
}

//返回房型列表，可供外部程序调用
public mapping *query_house_type()
{
    return house_type;
}

//返回地块列表，可供外部程序调用
public mapping *query_house_base()
{
    return house_base;
}

//显示当前可供建造的房型列表
public int show_type(object me)
{
    int i;
    string type, msg;

    msg = HIC"\n「"HIY + MUD_NAME + HIC"」目前可供建造的屋宅类型有：\n" NOR;
    msg += HIG "≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n" NOR;

    for (i = 0; i < sizeof(house_type); i++)
    {
        if(house_type[i]["type"] == "user") type = "玩家住宅";
        if(house_type[i]["type"] == "bang") type = "帮会驻地";
        if(house_type[i]["type"] == "xian") type = "散仙居所";
        msg += sprintf(HIW "名称：" HIY "%-10s" NOR
                       HIW "类别：" HIY "%-10s" NOR
                       HIW "间数：" HIY "%-4d" NOR
                       HIW "造价：" HIY"%-6d两黄金\n" NOR,
                       house_type[i]["name"],
                       type,
                       house_type[i]["rooms"],
                       house_type[i]["value"]);
    }

    msg += HIG "≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n" NOR;
    me->start_more(msg);
    return 1;
}

//选择想要建造的房型
public int choice_type(string arg, object me)
{
    int i, value;
    string name, code, type, entry;

    if(!arg)
        return notify_fail("请选择一种正确的屋宅类型。\n");

    for(i = 0; i < sizeof(house_type); i++)
    {
        if(arg != house_type[i]["name"])
            continue;
        code  = house_type[i]["code"];
        type  = house_type[i]["type"];
        name  = house_type[i]["name"];
        entry = house_type[i]["entry"];
        value = house_type[i]["value"];
    }

    set_temp("building_house/name", name, me);
    set_temp("building_house/code", code, me);
    set_temp("building_house/type", type, me);
    set_temp("building_house/entry", entry, me);
    set_temp("building_house/value", value, me);
    set_temp("building_house/val_t", value, me);
    tell_object(me, HIC "你选择了「"HIW + name + HIC"」这种屋宅，其造价为 "
                    HIY + value + " 两黄金" NOR);
    return 1;
}

//显示当前可用于建房的地块列表
public int show_base(object me)
{
    int i, j;
    object base;
    string msg, type;

    msg = HIC "\n「"HIY + MUD_NAME + HIC"」目前可供建造屋宅的地块有：\n" NOR;
    msg += HIG "≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n" NOR;

    for (i = 0; i < sizeof(house_base); i++)
    {
        if(house_base[i]["type"] == "user") type = "玩家住宅";
        if(house_base[i]["type"] == "bang") type = "帮会驻地";
        if(house_base[i]["type"] == "xian") type = "散仙居所";

        base = get_object(BASE_DIR + house_base[i]["file"]);
        if( query("house_build", base) >= query("max_build", base) )
            continue;
        j=query("max_build", base)-query("house_build", base);
        msg += sprintf(HIW "名称：" HIY "%-12s" NOR
                       HIW "地域：" HIY "%-8s" NOR
                       HIW "可建：" HIY "%-10s" NOR
                       HIW "剩余：" HIY "%-2d" NOR
                       HIW "地价：" HIY "%-6d两黄金\n" NOR,
                       house_base[i]["name"],
                       house_base[i]["place"], type, j,
                       house_base[i]["value"]);
    }

    msg += HIG "≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n" NOR;
    me->start_more(msg);
    return 1;
}

//选择想要建造房屋的地块
public int choice_base(string arg, object me)
{
    int i;
    mapping base;

    if(!arg)
        return notify_fail("请选择一个正确的地块名称。\n");

    for(i = 0; i < sizeof(house_base); i++)
    {
        if(house_base[i]["name"] == arg)
        {
            base = ([
                        "name"  : house_base[i]["name"],
                        "place" : house_base[i]["place"],
                        "file"  : BASE_DIR + house_base[i]["file"],
                        "value" : house_base[i]["value"],
                    ]);
            set_temp("building_house/base", base, me);
            tell_object(me, HIC "你选择了「"HIW + arg + HIC"」这一地块，其地价为 "
                            HIY + base["value"] + " 两黄金" NOR);
            return 1;
        }
    }

    tell_object(me, YEL "没有「"HIW + arg + NOR YEL"」这个地块。\n" NOR);
    return 1;
}

//在选定的地块上建造出所选类型的屋宅
public int build_house(object me)
{
    int i, j;
    string name, type, file, code, path, entry, zhuan, pass;
    mapping house, build, base, npc_data;
    object obj;
    string *room, *key;

    name=query_temp("building_house/name", me);
    base=query_temp("building_house/base", me);
    type=query_temp("building_house/type", me);
    code=type+"/"+query_temp("building_house/code", me)+"/";

    if(type == "bang")
    {
        path=HOUSE_DIR+type+"/"+query("bang/name", me);
    }
    if(type == "user" || type == "xian")
    {
        path=HOUSE_DIR+type+"/"+query("id", me);
    }

    if( !query_temp("building_house/path", me) )
        file  = SOURCE_DIR + code;
    else
        file=query_temp("building_house/path", me)+"/";

    entry=path+"/"+query_temp("building_house/entry", me);
    house = ([]);
    if( !query("house/build", me) )
        build = ([]);
    else
        build=query("house/build", me);

    reset_eval_cost();
    CMD_CP->copy_dir(file, path);

    room = get_dir(path + "/");
    for(i = 0; i < sizeof(room); i++)
    {
        reset_eval_cost();
        obj = load_object(path + "/" + room[i]);
        set("owner",query("id",  me), obj);//设置物件的管理者ID
        if(obj->is_house_huyuan()                           /*物件的属性是护院*/
             && query("owner_name", obj) == "某人"/*非转让由原型生成*/
             && query("set_skill/owner", obj) == "HOUSE_D")/*未改换过技能种类*/
        {
            npc_data=query_temp("rebuild_house/npc_data", me);
            if(mapp(npc_data) && sizeof(npc_data) > 0)  //原址改建技能不变
            {
                reset_eval_cost();
                key = keys(npc_data);
                for(j = 0; j < sizeof(key); j++)
                {
                    if(key[j] == "level"                /*技能等级取较高者保留*/
                         && npc_data[key[j]]>query("set_skill/level", obj) )
                            set("set_skill/level", npc_data[key[j]], obj);
                    else
                        if(key[j] == "skill")
                            set("generation_skill/code", npc_data[key[j]], obj);
                    else
                        set(key[j], npc_data[key[j]], obj);
                }
                //按照原有技能重新生成
                FACTION_D->gen_npc(obj,query("generation_skill/code", obj));
            }
            else
                FACTION_D->gen_npc(obj, 0);                 //随机选择某一种技能
        }
        if( query("max_laodu", obj)/*大门牢度取较高者保留*/
             && query("max_laodu", obj)<query_temp("rebuild_house/max_laodu", me) )
        {
            set("max_laodu",query_temp("rebuild_house/max_laodu",  me), obj);
            set("now_laodu",query_temp("rebuild_house/max_laodu",  me), obj);
        }
        if(type == "bang")
        {
            set("owner_name",query("bang/name",  me), obj);//帮会名称为管理者名
            if(obj->is_board())
            {
                obj->set_name(query("bang/name", me)+"的帮会留言板",({"board"}));
                set("location", path+"/xiaoting", obj);
            }
        }
        else
            if(type == "user" || type == "xian")
        {
            set("owner_name", me->name(1), obj);//屋主姓名为管理者名
        }
        set("path", path, obj);
        set("type", type, obj);
        obj->save();
        destruct(obj);
    }

    house += ([
        "name":query_temp("building_house/name", me),
        "code":query_temp("building_house/code", me),
        "value":query_temp("building_house/value", me),
        "zhuan":query_temp("building_house/zhuan", me),
        "entry" : entry,
        "path"  : path,
        "base"  : base,
    ]);

    pass = random_generation_password(8);
    house += ([ "pass" : pass, ]);
    build+=([type:query_temp("building_house/name", me),]);
    if( query_temp("building_house/build", me )
         && !query_temp("wiz_zhuan", me))//有标志则从帐户内扣钱
            addn("bank/gold", -house["value"], me);

//系统日志记录
    log_file("money/house", sprintf("%s：%s(%s)在%s建造%s一套，"
                                    "费用 %d 两黄金。\n", log_time(),
                                                          me->name(1),
                                                          query("id", me),
                                                          base["name"],
                                                          name,
                                                          house["value"]));

    if( query_temp("rebuild_house/the_value", me))//改建总价值需加上旧宅价值
        house["value"]+=query_temp("rebuild_house/the_value", me);
    set("house/"+type, house, me);
    set("house/build", build, me);
    add_entry(me, type);

    tell_object(me, BEEP + BLINK + HIC "\n恭喜！你现在已经在「"
                                   HIW + base["name"] + HIC"」拥有一套「"
                                   HIY + name + HIC"」了！\n" NOR);

    tell_object(me, HIW "这套屋宅的编码为『"HIY + pass + HIW"』，请牢记"
                        "并妥善保管好这个编码。\n" NOR);
//系统信息提示
    sys_info(me->name(1)+"("+query("id", me)+")在"
                         + base["name"] + "拥有了一套" + name + "。");

    delete_temp("building_house", me);
    me->save();
    return 1;
}

//新建屋宅完工后，需在所处地块增添相应入口
private int add_entry(object me, string arg)
{
    object room, door;
    mapping type;
    string entry;

    if( !query("house/"+arg, me) )
        return 1;

    type=query("house/"+arg, me);
    room  = get_object(type["base"]["file"]);
    entry = type["entry"];
    if( query("can_build", room) == "bang" )
    {
        set("exits/enter", entry, room);
    }
    else
        if( query("can_build", room) == "user"
             || query("can_build", room) == "xian" )
    {
        set("exits/"+query("id", me), entry, room);
    }
    addn("house_build", 1, room);
    room->save();

    door  = get_object(type["entry"]);
    entry = type["base"]["file"];
    set("exits/out", entry, door);
    door->save();
    return 1;
}

//旧有屋宅拆除后，需在原处地块删除相应入口
private int del_entry(object me, string arg)
{
    int i;
    object room;
    mapping type;

    if( !query("house/"+arg, me) )
        return 1;

    type=query("house/"+arg, me);
    room = get_object(type["base"]["file"]);
    if( query("can_build", room) == "bang" )
    {
        delete("exits/enter", room);
    }
    else
        if( query("can_build", room) == "user"
             || query("can_build", room) == "xian" )
    {
        delete("exits/"+query("id", me), room);
    }
    addn("house_build", -1, room);
    room->save();
    return 1;
}

//将自己拥有的某处屋宅转让给他人
public int do_cession(object me, object ob, string arg)
{
    int i, value, new_value, v1, nv1;
    mapping house, new_house;
    string zhuan, entry;

    house=query("house/"+arg, me);
    if(!house)
    {
        tell_object(me, YEL "你有建造过这种屋宅吗？\n" NOR);
        return 1;
    }

    if( query("house/"+arg, ob) )
    {
        tell_object(me, YEL "\n转让失败！" + ob->name() +
                            "已经拥有这种屋宅了。\n" NOR);
        return 1;
    }

    if(arg == "user" && wizhood(ob) != "(player)")
    {
        tell_object(me, YEL + "\n转让失败！" + ob->name() +
                              "已经不再需要这些凡俗事物了。\n" NOR);
        return 1;
    }

    if(arg == "xian" && !wizardp(ob) && wizhood(ob) != "(immortal)")
    {
        tell_object(me, YEL + "转让失败！\n" + ob->name() +
                        "还没有位列上界仙班，不能获取这种屋宅。\n" NOR);
        return 1;
    }

    if( arg == "bang" && query("bang/class", ob) != 1 )
    {
        tell_object(me, YEL + "转让失败！\n" + ob->name() +
                        "尚未登上帮主宝座，不能获取这种屋宅。\n" NOR);
        return 1;
    }

    if( !query_temp("cession_house/name", me) )
        zhuan = house["zhuan"];
    else
        zhuan=me->name(1)+"("+query("id", me)+")";

    value = house["value"];
    if(zhuan == "HOUSE_D")
    {
        new_value = value;
              nv1 = 0;
               v1 = 0;
    }
    else
    {
        new_value = value + value/10;
              nv1 = new_value;
               v1 = value;
        if( query("bank/gold", ob)<new_value )
        {
            tell_object(me, YEL + "\n\n转让失败！" + ob->name() +
                                  "的钱庄存款不够支付总计"
                            HIY + chinese_number(new_value) + "两黄金" NOR
                            YEL "的房产价值及手续费。\n" NOR);
            tell_object(ob, YEL "\n\n转让失败！你的钱庄存款不够支付总计"
                            HIY + chinese_number(new_value) + "两黄金" NOR
                            YEL "的房产价值及手续费。\n" NOR);
            return 1;
        }
    }

    for(i = 0; i < sizeof(house_type); i++)
    {
        if(house["name"] != house_type[i]["name"])
            continue;
        entry = house_type[i]["entry"];
    }

    new_house = ([
        "name"  : house["name"],
        "code"  : house["code"],
        "base"  : house["base"],
        "path"  : house["path"],
        "type"  : arg,
        "entry" : entry,
        "value" : new_value,
        "zhuan" : zhuan,
        "build" : "cession",
    ]);

    set_temp("building_house", new_house, ob);

    if(arg == "bang")   //帮会驻地无需拆除，只需重新设定
    {
        no_dismantle(me, ob, arg);
    }
    else
        if(arg == "user" || arg == "xian")
    {
        build_house(ob);        //建造被转让者的新屋宅
        do_dismantle(me, arg);  //拆除出让者原有的旧屋
    }

    if(nv1 > 0)
    {
        tell_object(ob, BEEP + BLINK + HIC "房产价值及手续费共计"
                             + HIY + chinese_number(nv1) + "两黄金"
                               HIC "已从你的钱庄帐户内扣除。\n" NOR);
    }

    addn("bank/gold", v1, me);
    if(v1 > 0)
    {
        tell_object(me, BEEP + BLINK + HIC "转让成功！房产价值"
                             + HIY + chinese_number(v1) + "两黄金"
                               HIC "已转入你的钱庄帐户内。\n" NOR);
    }
    return 1;
}

//将所选定的某处屋宅拆除
public int do_dismantle(object me, string arg)
{
    int i, j;
    string path, *key, *room;
    mapping build, type;
    object obj;

    build=query("house/build", me);
    if(sizeof(build) == 0)
        return 1;

    key = sort_array(keys(build), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        if(key[i] == arg)
        {
            type=query("house/"+arg, me);
            path = type["path"];
            room = get_dir(path + "/");
            for(j = 0; j < sizeof(room); j++)
            {
                reset_eval_cost();
                obj = get_object(path + "/" + room[j]);
                destruct(obj);
            }
            del_entry(me, arg);
            CMD_RM->rm_dir(path);
            CMD_RM->rm_dir(DATA_DIR + path);
            tell_object(me, BEEP + BLINK + HIR "\n你在「"
                                           HIW + type["base"]["name"] +
                                           HIR"」的「"HIY + type["name"] +
                                           HIR"」已经不存在了！\n" NOR);
            //系统信息提示
            sys_info(me->name(1)+"("+query("id", me)+")在"
                                 + type["base"]["name"] + "的"
                                 + type["name"] + "现已拆除。");
            //系统日志记录
            log_file("money/house", sprintf("%s：%s(%s)在%s的%s拆除。\n",
                                                          log_time(),
                                                          me->name(1),
                                                          query("id", me),
                                                          type["base"]["name"],
                                                          type["name"]));
            delete("house/"+arg, me);
            map_delete(build, key[i]);
            set("house/build", build, me);
            if(sizeof(build) == 0)
                delete("house", me);
            return 1;
        }
    }
    return 1;
}

//房屋不拆除，只重新设定主人信息，用于帮主传位，无资金流动
public int no_dismantle(object me, object ob, string arg)
{
    int i;
    object obj;
    string path, pass, *key, *room;
    mapping house, build, type;

    //清除旧主人的有关数据
    build=query("house/build", me);
    if(sizeof(build) == 0)
        return 1;
    key = sort_array(keys(build), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        if(key[i] == arg)
        {
            type=query("house/"+arg, me);
            path = type["path"];
            pass = type["pass"];
            delete("house/"+arg, me);
            map_delete(build, key[i]);
            set("house/build", build, me);
            if(sizeof(build) == 0)
                delete("house", me);
            me->save();
        }
    }

    //设置屋宅的新主人数据
    path=query_temp("building_house/path", ob);
    room = get_dir(path + "/");
    for(i = 0; i < sizeof(room); i++)
    {
        obj = get_object(path + "/" + room[i]);
        if(arg == "bang")
        {
            set("owner_name",query("bang/name",  ob), obj);
        }
        else
            if(arg == "user" || arg == "xian")
        {
            set("owner_name", ob->name(1), obj);
        }
        set("owner",query("id",  ob), obj);
        set("path", path, obj);
        set("type", arg, obj);
        obj->save();
        destruct(obj);
    }

    //设置新主人的有关数据
    house = ([]);
    if( !query("house/build", ob) )
        build = ([]);
    else
        build=query("house/build", ob);

    house += ([
        "name":query_temp("building_house/name", ob),
        "code":query_temp("building_house/code", ob),
        "value":query_temp("building_house/value", ob),
        "zhuan":query_temp("building_house/zhuan", ob),
        "entry":query_temp("building_house/entry", ob),
        "path":query_temp("building_house/path", ob),
        "base":query_temp("building_house/base", ob),
        "pass"  : pass,
    ]);

    build+=([arg:query_temp("building_house/name", ob),]);
    set("house/"+arg, house, ob);
    set("house/build", build, ob);
    delete_temp("building_house", ob);
    ob->save();

    //系统信息提示
    sys_info(me->name(1)+"("+query("id", me)+")与"+
             ob->name(1)+"("+query("id", ob)+")进行了房产交接。");

    //系统日志记录
    log_file("money/house", sprintf("%s：%s(%s)与%s(%s)"
                                    "进行了房产交接。\n", log_time(),
                                                          me->name(1),
                                                          query("id", me),
                                                          ob->name(1),
                                                          query("id", ob)));
    return 1;
}

//房主自杀或被清档，原有的所有屋宅将被自动拆除
public int do_dismantle_all(object me)
{
    int i;
    string *key, arg;
    mapping build;

    build=query("house/build", me);
    if(sizeof(build) == 0)
        return 1;

    key = sort_array(keys(build), 1);
    for(i = 0; i < sizeof(key); i++)
    {
        arg = key[i];
        do_dismantle(me, arg);
        continue;
    }
    return 1;
}

//设定房间名称
public int do_short(object me, string arg)
{
    if(!arg)
    {
        tell_object(me, "指令格式：setname <房间名字>\n");
        return 1;
    }
    if(CHINESE_D->check_control(arg))
        return notify_fail("名字不可有控制符！\n");
    if(CHINESE_D->check_space(arg))
        return notify_fail("名字必需不含空格！\n");
    if(CHINESE_D->check_return(arg))
        return notify_fail("名字必需不含回车键！\n");
    if(!CHINESE_D->check_chinese(arg))
        return notify_fail("名字必须使用中文！\n");
    if(strlen(arg) > 14)
        return notify_fail("名字最长只能七个汉字！\n");

    tell_object(me, "设置房间名字为：" + arg);
    tell_object(me,"...成功！\n");
    set("short", arg, environment(me));
    environment(me)->save();
    return 1;
}

//设定房内物品名称（目前仅开放茶水一项）
public int do_item(object me, string arg)
{
    string item, desc;
    object room = environment(me);

    if(!arg || sscanf(arg, "%s %s", item, desc) != 2)
        return notify_fail("指令格式：setitem <物品> <名称>\n");
    if(item != "茶水")
        return notify_fail("目前只能设定「茶水」的名称。\n");
    if( !query("resource/water", room) )
        return notify_fail("只有客厅内才可以设置茶水名称。\n");

    desc = trans_color(desc);
    if(!CHINESE_D->check_chinese(filter_color(desc)))
        return notify_fail("物品名称必需使用中文！\n");
    if(CHINESE_D->check_control(filter_color(desc)))
        return notify_fail("物品名称不可有控制符！\n");
    if(CHINESE_D->check_space(filter_color(desc)))
        return notify_fail("物品名称必需不含空格！\n");
    if(strlen(filter_color(desc)) > 14)
        return notify_fail("物品名称最多为七个汉字，支持颜色代码。\n");
    if(member_array(filter_color(desc), banned_name) != -1)
        return notify_fail("这种名字不太好吧......\n");
    set("resource/water", desc, room);
    room->save();
    tell_object(me, "设定茶水名称为「" + desc + NOR"」...成功！\n");
    return 1;
}

//开始设定房间详细描述
public int do_long(object me)
{
    string arg = "";

    tell_object(me, "描述最多为五行，在行首输入 . 表示结束。第一行首会自动加两个空格。\n");
    tell_object(me, "------------------------------------------------------------\n");
    input_to("get_long", arg, me);
    return 1;
}

//输入编辑房间详细描述
public int get_long(string msg, string arg, object me)
{
    int i=query("long_line", environment(me));

    if(msg == ".")
    {
        if(i > 5)
        {
            write("设定失败，描述不能超过五行。\n");
            delete("long_line", environment(me));
            return 1;
        }
        else
        {
            set("long", arg, environment(me));
            delete("long_line", environment(me));
            environment(me)->save();
            tell_object(me, "设定房间描述...成功！\n");
            return 1;
        }
    }

    if(strlen(msg) > 60)
    {
        write("每行字数最多为三十个（包括空格与标点），请重新输入本行。\n");
        input_to("get_long", arg, me);
        return 1;
    }
    arg += msg + "\n";
    addn("long_line", 1, environment(me));
    input_to("get_long", arg, me);
    return 1;
}

//查看大门当前状况，房主可查看到当前及最大牢度
public int look_house_door(string arg, object me, object ob)
{
    int i;
    string msg;

    if(!arg || arg == "")
        return 0;

    if(arg != "men"
        && arg != "door"
        && arg != "门"
        && arg != "大门")
            return 0;

    if( query("id", me) == query("owner", ob) )
    {
        tell_object(me, HIW "目前大门的最大牢度为『"HIY
                        +chinese_number(query("max_laodu", ob) )
                        + HIW"』点，当前牢度为「"HIY
                        +chinese_number(query("now_laodu", ob) )
                        + HIW"」点。\n" NOR);
        if( query("type", ob) != "xian" )
        {
            tell_object(me, "你可以用黄金来加固(jiagu)大门，"
                            "每一两黄金可以提高一点牢度。\n");
        }
        return 1;
    }
    else
    {
        i=query("now_laodu", ob);
        if(i <= 0)
            msg = "已全然毁坏";
        else
            if(i < 100)
                msg = "已不堪一击";
        else
            if(i >= 100 && i < 300)
                msg = "已摇摇欲坠";
        else
            if(i >= 300 && i < 500)
                msg = "已损坏颇多";
        else
            if(i >= 500 && i < 1000)
                msg = "不甚可靠";
        else
            if(i >= 1000 && i < 3000)
                msg = "尚算结实";
        else
            if(i >= 3000 && i < 6000)
                msg = "结实可靠";
        else
            if(i >= 6000 && i < 10000)
                msg = "颇为牢固";
        else
            if(i >= 10000 && i < 20000)
                msg = "极其坚固";
        else
            if(i >= 20000 && i < 30000)
                msg = "牢不可破";
        else
            if(i >= 30000 && i < 1000000)
                msg = "固若金汤";
        else
            if(i >= 1000000)
                msg = "宛若神铸";

        tell_object(me,"这是"+query("owner_name", ob)+
                        "的大门，看上去似乎" + msg + "。\n");
        return 1;
    }
}

//房主用身上的黄金来加固大门的牢度
public int jiagu_house_door(string arg, object me, object ob)
{
    object gold;
    mapping house;
    int how, value;

    if( query("id", me) != query("owner", ob) )
        return notify_fail("什么？\n");

    if(!arg || sscanf(arg, "%d gold", how) != 1)
        return notify_fail("你要出多少两黄金(" HIG "jiagu *** gold" NOR
                           ")来加固大门的牢度？\n");

    if(!(gold = present("gold_money", me)))
        return notify_fail("你身上好象没有带黄金吧？\n");

    if(how < 1)
        return notify_fail("你要出多少两黄金(" HIG "jiagu *** gold" NOR
                           ")来加固大门的牢度？\n");

    if((int)gold->query_amount() < how)
        return notify_fail("你身上好象没有带这么多的黄金吧？\n");

    if( query("type", ob) == "xian" )
        return notify_fail("仙宅大门非人力所能破坏，无须再加固了。\n");

    gold->add_amount(-how);
    addn("max_laodu", how, ob);
    addn("now_laodu", how, ob);
    ob->save();
    house  = query("house/" + query("type", ob), me);
    value  = house["value"] + how;
    house += ([ "value" : value, ]);
    me->save();
    message_vision("$N想了想，有点犹豫地从身上掏出"HIY + chinese_number(how) +
                   "两黄金"NOR"，仔细地镶在了大门上。\n"
                   HIC"\n\t"+query("owner_name", ob)+"的大门因为增加了"
                       "黄金含量，牢度提高了！\n\n" NOR, me);
    tell_object(me, HIW "目前大门的最大牢度为『"HIY
                    +chinese_number(query("max_laodu", ob) )
                    + HIW"』点，当前牢度为「"HIY
                    +chinese_number(query("now_laodu", ob) )
                    + HIW"」点。\n" NOR);
    return 1;
}

//房主与其配偶（帮会总部包括帮会成员）及被邀请的宾客可推门进入屋内
public int push_house_door(string arg, object me, object ob)
{
    object obj;
    string path, room;

    if(arg != "men"
        && arg != "door"
        && arg != "门"
        && arg != "大门")
            return notify_fail("你要推什么？\n");

    if(query("exits/" + query("set_exits",ob)), ob)
        return notify_fail("门已经被别人轰破了，你直接进去吧！\n");

    if(query("exits/" + query("forbid_exits",ob)), ob)
        return notify_fail("门是开着的，你直接进去吧！\n");

    path=query("path", ob)+"/";
    room=path+query("set_entry", ob);

    if( query("type", ob) == "bang" )
    {
        if( query("id", me) == query("owner", ob )
             || query("couple/couple_id", me) == query("owner", ob )
             || query("bang/name", me) == query("owner_name", ob) )
        {
            if(objectp(obj = present("hu yuan", environment(me)))
                 && query("owner", obj) == query("owner", ob )
                && obj->is_livings() && !obj->is_fighting())
            {
                message_vision("$N对$n躬身施了一礼：“您回来啦！"
                               "一路辛苦了，快请进吧！”\n", obj, me);
            }
            message_vision("$N将门一推，径直走了进去。\n", me);
            tell_room(room, "有人推开门走了进来。\n");
            me->move(room);
            return 1;
        }

        if(query_temp("invited_guest/" + query("owner",ob)),me)
        {
            if(objectp(obj = present("hu yuan", environment(me)))
                 && query("owner", obj) == query("owner", ob )
                && obj->is_livings() && !obj->is_fighting())
            {
                message_vision("$N看了看$n，点头道：“原来是贵客登门，"
                               "快请进吧！”\n", obj, me);
            }
            message_vision("$N将门轻轻推开，走了进去。\n", me);
            me->move(room);
            return 1;
        }
    }
    else
        if( query("type", ob) == "user" || query("type", ob) == "xian" )
    {
        if( query("id", me) == query("owner", ob )
             || query("couple/couple_id", me) == query("owner", ob) )
        {
            if(objectp(obj = present("hu yuan", environment(me)))
                 && query("owner", obj) == query("owner", ob )
                && obj->is_livings() && !obj->is_fighting())
            {
                message_vision("$N对$n躬身施了一礼：“您回来啦！"
                               "一路辛苦了，快请进吧！”\n", obj, me);
            }
            message_vision("$N将门一推，径直走了进去。\n", me);
            me->move(room);
            return 1;
        }

        if(query_temp("invited_guest/" + query("owner",ob)),me)
        {
            if(objectp(obj = present("hu yuan", environment(me)))
                 && query("owner", obj) == query("owner", ob )
                && obj->is_livings() && !obj->is_fighting())
            {
                message_vision("$N看了看$n，点头道：“原来是贵客登门，"
                               "快请进吧！”\n", obj, me);
            }
            message_vision("$N将门轻轻推开，走了进去。\n", me);
            tell_room(room, "有人推开门走了进来。\n");
            me->move(room);
            return 1;
        }
    }
    else
        return 0;
}

//无权推门入内者可打倒护院，再攻破大门闯入
public int break_house_door(string arg, object me, object ob)
{
    int i;
    object obj, where;
    string path, room, *file;

    if(!arg || arg == "")
        return 0;

    if(arg != "men"
        && arg != "door"
        && arg != "门"
        && arg != "大门")
            return 0;

    if(query("exits/" + query("set_exits",ob)),ob)
        return notify_fail("门已经被轰开了。\n");

    if( query("type", ob) == "bang" )
    {
        if( query("bang/name", me) == query("owner_name", ob) )
            return notify_fail("你是不是吃错药了？要轰自家帮里的大门？\n");
    }
    else
        if( query("type", ob) == "user" )
    {
        if( query("id", me) == query("owner", ob )
             || query("couple/couple_id", me) == query("owner", ob) )
                return notify_fail("你是不是吃错药了？要轰自家的大门？\n");
    }
    else
        if( query("type", ob) == "xian" )
    {
        if( query("id", me) == query("owner", ob )
             || query("couple/couple_id", me) == query("owner", ob) )
                return notify_fail("你是不是吃错药了？要轰自家的大门？\n");
        else
            return notify_fail("仙宅大门也是你能破坏得了的吗？省省力气吧！\n");
    }

    path=query("path", ob)+"/";
    room=path+query("set_entry", ob);

    if(objectp(obj = present("hu yuan", environment(me)))
         && query("owner", obj) == query("owner", ob )
        && obj->is_livings())
    {
        message_vision("$N沉声对$n喝道：“哪来的歹徒，敢到这里来撒野？"
                       "快给我滚远点！”\n", obj, me);
        return 1;
    }

    //最大内力需超过100方可攻门
    if( query("max_neili", me)<100 )
        return notify_fail("你的内力太少，无法运气发力轰门。\n");

    //当前内力全满方可出手攻门
    if( query("neili", me)<query("max_neili", me) )
        return notify_fail("你目前的内力不够充盈，无法运气发力轰门。\n");

    message_vision("$N凝神运气，大吼一声：“开！”双掌一缩一吐，"
                   "一股掌力疾奔而去......\n", me);

    file = get_dir(path);
    for(i = 0; i < sizeof(file); i++)   //整套屋宅的所有房间都可得到轰门警示
    {
        where = get_object(path + file[i]);
        if(where == environment(me))    //攻门者所处的（大门场景）忽略
            continue;
        tell_room(where, BEEP + HIW "\n大门处突然传来“轰”地一声巨响，"
                         "好象是有人在发力轰门！\n\n" NOR);
    }

    //攻门者当前内力超过大门当前牢度的20倍则门被攻破
    if( query("neili", me)>query("now_laodu", ob)*20 )
    {
        for(i = 0; i < sizeof(file); i++)//整套屋宅的所有房间都可得到门破警示
        {
            where = get_object(path + file[i]);
            if(where == environment(me))    //攻门者所处的（大门场景）忽略
                continue;
            tell_room(where, BEEP + HIR "\n大门处突然传来“轰”地一声巨响，"
                         "听上去是大门已经被轰开了！\n\n" NOR);
        }
        message_vision("只听“轰”地一声响，$N已把"
                       +query("owner_name", ob)+"的大门震开了！\n",me);
        addn("neili", -(query("now_laodu", ob)), me);
        set("exits/"+query("set_exits", ob), room, ob);
        set("now_laodu", 0, ob);
        return 1;
    }
    else    //大门降低攻门者内力的1/20牢度，有待继续
    {
        message_vision("只听“轰！”地一声响，大门晃了几晃，震落了不少的尘土。\n", me);
        addn("now_laodu", -(query("neili", me)/20), ob);
        set("neili", 0, me);
        return 1;
    }
    return 1;
}

//屋宅管理者可修改护院的姓名、头衔、昵称、描述等内容
public int modify_huyuan(string arg, object me, object ob)
{
    string item, msg, gender;
    mapping dbase;
    int i = strlen(msg);

    if(!arg || sscanf(arg, "%s %s", item, msg) != 2)
        return notify_fail(HIW "\n指令格式: modify <款项> <内容>\n"
                           "\n款项包括：\n"
                           "\tname       名字\n"
                           "\tnickname   外号\n"
                           "\ttitle      头衔\n"
                           "\tgender     性别\n"
                           "\tdesc       描述\n"
                           "\nmodify [nickname|title|desc] none 表示删除。\n" NOR);

    if(!ob->is_livings())
        return notify_fail("嗯....你得先把" + ob->name(1) + "弄醒再说。\n");

    if(ob->is_fighting())
        return notify_fail("嗯....你得先等" + ob->name(1) + "打完架再说。\n");

    switch(item)
    {
        case "desc":
        if(CHINESE_D->check_length(filter_color(msg)) > 100)
            return notify_fail("你设定的描述太长了。\n");
        if(msg == "none")
        {
            delete("long", ob);
            ob->save();
            return notify_fail("删除护院描述...成功！\n");
        }
        set("long", trans_color(msg)+"\n", ob);
        ob->save();
        return notify_fail("设定护院描述...成功！\n");

        case "nickname" :
        if(CHINESE_D->check_length(filter_color(msg)) > 20)
            return notify_fail("你设定的外号太长了。\n");
        if(msg == "none")
        {
            delete("nickname", ob);
            ob->save();
            return notify_fail("删除护院外号...成功！\n");
        }
        set("nickname", trans_color(msg), ob);
        ob->save();
        return notify_fail("设定护院外号...成功！\n");

        case "title" :
        if(CHINESE_D->check_length(filter_color(msg)) > 20)
            return notify_fail("你设定的头衔太长了。\n");
        if(msg == "none")
        {
            delete("title", ob);
            ob->save();
            return notify_fail("删除护院头衔...成功！\n");
        }
        set("title", trans_color(msg), ob);
        ob->save();
        return notify_fail("设定护院头衔...成功！\n");

        case "name" :
        if(CHINESE_D->check_control(msg))
            return notify_fail("名字不可有控制符！\n");
        if(CHINESE_D->check_space(msg))
            return notify_fail("名字必需不含空格！\n");
        if(CHINESE_D->check_return(msg))
            return notify_fail("名字必需不含回车键！\n");
        if(!CHINESE_D->check_chinese(msg))
            return notify_fail("名字必需使用中文！\n");
        if(CHINESE_D->check_length(msg) > 10)
            return notify_fail("你设定的名字太长了。\n");
        if(member_array(msg, banned_name) != -1)
            return notify_fail("这种名字不太好吧......\n");
        if(!"/adm/daemons/ban_named"->valid_name(msg))
            return notify_fail("对不起，这种名字会造成其他人的困扰。\n");
        dbase = ob->query_entire_dbase();
        dbase["name"] = msg;
        set("modify/name", msg, ob);
        ob->save();
        return notify_fail("设定护院名字...成功！\n");

        case "gender" :
        if(msg != "男性" && msg != "女性")
            return notify_fail("性别必须为男性或女性其中一种！\n");
        gender=query("generation_skill/gender", ob);
        if( query("gender", ob) == msg )
            return notify_fail("护院当前的性别已经是" + msg + "了。\n");
        if(gender == "male" && msg == "女性")
            return notify_fail("设定无效，护院当前所使用的技能仅限男性。\n");
        if(gender == "female" && msg == "男性")
            return notify_fail("设定无效，护院当前所使用的技能仅限女性。\n");
        set("gender", msg, ob);
        ob->save();
        return notify_fail("设定护院性别...成功！\n");
    }
    return notify_fail("你要设定什么？\n");
}

//屋宅管理者可增加、删减、查看保存在护院处的贵宾列表
public int add_guest(string arg, object me, object ob)
{
    int i, how;
    string who, msg, *key;
    mapping vip;

    msg = HIW "\n增加贵宾：setvip <ID> -add\n"
              "删除贵宾：setvip <ID> -del\n"
              "贵宾列表：setvip  -list\n" NOR;

    if(!arg || arg == "")
        return notify_fail(msg);

    if(!ob->is_livings())
        return notify_fail("嗯....你得先把" + ob->name(1) + "弄醒再说。\n");

    if(ob->is_fighting())
        return notify_fail("嗯....你得先等" + ob->name(1) + "打完架再说。\n");

    vip=query("vip", ob);
    how=query("vip_limit", ob);
    if((int)how <= 0)
        how = VIP_ORIGIN;
    if(arg == "-list")
    {
        msg = ob->name(1) + "悄声告诉你：";
        if(sizeof(vip) == 0)
        {
            msg += "目前没有设定任何贵宾。\n";
            msg += sprintf(WHT "当前最多可设定" HIY "%s" NOR WHT "位贵宾，剩余"
                           HIW "%s" NOR WHT "个空位。\n" NOR,
                            chinese_number(how), chinese_number(how - sizeof(vip)));
            return notify_fail(msg);
        }
        msg += "\n目前在贵宾名单上有如下玩家：\n";
        msg += HIG "------------------------------\n" NOR;
        key = sort_array(keys(vip), 1);
        for(i = 0; i < sizeof(key); i++)
        {
            msg += HIY + key[i] + "\n" NOR;
        }
        msg += HIG "------------------------------\n" NOR;
        msg += "共有 " HIC + chinese_number(sizeof(vip)) + NOR " 位贵宾。\n";
        msg += sprintf(WHT "当前最多可设定" HIY "%s" NOR WHT "位贵宾，剩余"
                       HIW "%s" NOR WHT "个空位。\n" NOR,
                        chinese_number(how), chinese_number(how - sizeof(vip)));
        return notify_fail(msg);
    }
    else
        if(sscanf(arg, "%s -add", who))
    {
        if( query("id", me) == who
             || query("couple/couple_id", me) == who )
        {
            msg = ob->name(1) + "笑道：直接推门就能进去的，不用加进贵宾名单。\n";
            return notify_fail(msg);
        }
        if( query("vip/"+who, ob) )
        {
            msg = ob->name(1) + "笑道：「" + who + "」已经在贵宾名单之中了。\n";
            return notify_fail(msg);
        }
        if(sizeof(vip) >= how)
        {
            msg = ob->name(1) + "摇头道：目前已经定义了足够多的贵宾名单了。\n";
            return notify_fail(msg);
        }
        set("vip/"+who,query("id",  me), ob);
        ob->save();
        msg = ob->name(1) + "点头道：「" + who + "」已被列入贵宾名单之中。\n";
        return notify_fail(msg);
    }
    else
        if(sscanf(arg, "%s -del", who))
    {
        if( !query("vip/"+who, ob) )
        {
            msg = ob->name(1) + "摇头道：「" + who + "」目前并不在贵宾名单上。\n";
            return notify_fail(msg);
        }
        delete("vip/"+who, ob);
        ob->save();
        msg = ob->name(1) + "点头道：「" + who + "」已经从贵宾名单中删除。\n";
        return notify_fail(msg);
    }
    else
        return notify_fail(msg);
}

//屋宅管理者可花钱扩充护院处的贵宾列表上限
public int add_vip_limit(int value, object me, object ob)
{
    int i, how, new_value;
    object huyuan, *list;
    mapping house;

    huyuan=get_object(query_temp("house_addvips/huyuan", me));
    if(!huyuan)
        return notify_fail("护院物件搜寻错误。\n");

    if( query("bank/gold", me)<value )
        return notify_fail("你的存款不够。\n");

    how=query("vip_limit", huyuan);//获取原有贵宾上限
    if((int)how <= 0)
        how = VIP_ORIGIN;

    how += 1;
    set("vip_limit", how, huyuan);//增加一个贵宾上限
    huyuan->save();
    list = children(file_name(huyuan));
    for(i = 0; i < sizeof(list); i++)
    {
        if(environment(list[i]))
            destruct(environment(list[i]));
    }

    house = query("house/" + huyuan->query("type",huyuan),me);
    new_value = house["value"] + value;
    house += ([ "value" : new_value, ]);    //费用计入屋宅价值
    addn("bank/gold", -value, me);//从存款中扣除费用
    me->save();
    delete_temp("house_addvips", me);
    tell_object(me, sprintf(HIC "\n%s对你点头笑道：贵宾限额已扩充为%s位，"
                                "费用%s两黄金已从你的存款内扣除。\n" NOR,
                                    ob->name(1), chinese_number(how),
                                    chinese_number(value)));
    return 1;
}

//贵宾列表中有名字的，向护院查询后可获得推门入内的临时权限
public int ask_guest(object me, object ob)
{
    if(!ob->is_livings())
        return 0;

    if(ob->is_fighting())
        return notify_fail("嗯....你得先等" + ob->name(1) + "打完架再说。\n");

    if( query("type", ob) == "bang" )
    {
        if( query("bang/name", me) == query("owner_name", ob) )
        {
            message_vision("$N对$n躬身施了一礼：“您回来啦！"
                           "一路辛苦了，快请进吧！”\n", ob, me);
            return 1;
        }
    }
    else
        if( query("type", ob) == "user" || query("type", ob) == "xian" )
    {
        if( query("id", me) == query("owner", ob )
             || query("couple/couple_id", me) == query("owner", ob) )
        {
            message_vision("$N对$n躬身施了一礼：“您回来啦！"
                           "一路辛苦了，快请进吧！”\n", ob, me);
            return 1;
        }
    }

   if( query("vip/"+query("id", me)), ob)
    {
        set_temp("invited_guest/"+query("owner", ob), 1, me);
        message_vision("$N看了看$n，点头道：“原来是贵客登门，"
                       "快请进吧！”\n", ob, me);
        return 1;
    }
    else
    {
        message_vision("$N打量了$n几眼，疑惑的摇了摇头。\n", ob, me);
        return 1;
    }
}

//屋宅管理者及其配偶可在屋内任意一处邀请某人前来作客
//被邀请者将获得推门进屋的临时权限
public int invite_guest(object me, string arg)
{
    int i;
    object ob, obj, *user;

    if(!arg || arg == "")
        return notify_fail("你想邀请谁来作客？\n");

    user = users();
    for(i = 0; i < sizeof(user); i++)
    {
        if( arg == user[i]->name(1) || arg == query("id", user[i]) )
            obj = user[i];
    }

    if( !obj || (wizardp(obj) && query("env/invisibility", obj)>1) )
        return notify_fail("你想邀请的人现在好象不在。\n");

    if(obj->is_ghost())
        return notify_fail("你想邀请的人似乎不在阳间。\n");

    if(!obj->is_livings())
        return notify_fail("你想邀请的人目前可能无法接收信息。\n");

    if( query("id", obj) == query("id", me) )
        return notify_fail("自己邀请自己？没搞错吧？\n");

    if( query("id", obj) == query("couple/couple_id", me) )
        return notify_fail("自己的配偶可以直接进来，无需邀请。\n");

    ob = environment(me);
    if( query("type", ob) == "bang"
         && query("bang/name", obj) == query("owner_name", ob) )
            return notify_fail("帮里的人可以直接进入帮会驻地，无需邀请。\n");

    set_temp("invited_guest/"+query("owner", ob), 1, obj);
    tell_object(me, HIC "你决定邀请" + obj->name() + "前来作客。\n" NOR);
    tell_object(obj, HIM "\n" + me->name(1) + "邀请你前去作客。\n" NOR);
    return 1;
}


//管理者可查询护院所使用的技能，并可获取所有可供选择的技能信息
public int ask_huyuan_faction(object me, object ob)
{
    string name, code, topic;

    if(!ob->is_livings())
        return notify_fail("嗯....你得先把" + ob->name(1) + "弄醒再说。\n");

    if(ob->is_fighting())
    {
        message_vision("$N对$n摇头道：有什么事等我打完架再说。\n", ob, me);
        return 1;
    }

    if( query("id", me) != query("owner", ob) && !wizardp(me) )
    {
        message_vision("$N对$n摇头道：这些不是你可以随便询问的。\n", ob, me);
        return 1;
    }

    name=query("generation_skill/name", ob);
    code=query("generation_skill/code", ob);
    if(!name)
    {
        FACTION_D->show_skill(me, 0);
        return 1;
    }

    topic=query_temp("last_ask/topic", me);
    if( query_temp("ask_all_faction", me) )
    {
        topic = "";
        FACTION_D->show_skill(me, 0);
    }
    else
        if(topic != name && topic != code)
    {
        message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                          "嘀咕了几句。\n", environment(me), ({ me, ob }));
        tell_object(me, HIW + ob->name(1) + "向你点头笑道：\n" NOR);
        FACTION_D->show_skill(me, topic);
    }

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "嘀咕了几句。\n", environment(me), ({ me, ob }));
    tell_object(me, HIW + ob->name(1) + "施了一礼道：我目前使用的技能是「"
                    HIY + name + HIW "」。\n" NOR);
    FACTION_D->show_skill(me, name);

    if( query_temp("query_faction", me )
         && !query_temp("ask_all_faction", me) )
    {
        tell_object(me, HIC "\n" + ob->name(1) + "悄声道：向我查询「"
                        HIG "武功总览" HIC "」可获取所有可选择的技能"
                            "信息。\n" NOR);
    }

    delete_temp("query_faction", me);
    delete_temp("ask_all_faction", me);
    return 1;
}

//管理者用身上的黄金来提升护院的技能等级
public int shenji_huyuan(string arg, object me, object ob)
{
    object gold;
    mapping house;
    int how, value;

    if( query("id", me) != query("owner", ob) )
        return notify_fail("什么？\n");

    if(!arg || sscanf(arg, "%d gold", how) != 1)
       return notify_fail("你要付多少两黄金(" HIG "shengji *** gold"NOR
                           ")来提升护院的等级？\n");

    if(!(gold = present("gold_money", me)))
        return notify_fail("你身上好象没有带黄金吧？\n");

    if((int)gold->query_amount() < how)
        return notify_fail("你身上好象没有带这么多的黄金吧？\n");

    if(how < 50 || how % 50 != 0)
        return notify_fail("升级护院的黄金数目必须是五十的整数倍。\n");

    if(!ob->is_livings())
        return notify_fail("嗯....你得先把" + ob->name(1) + "弄醒再说。\n");

    if(ob->is_fighting())
        return notify_fail("嗯....你得先等" + ob->name(1) + "打完架再说。\n");

    if( query("set_skill/level", ob) >= 900 )
    {
        ask_huyuan_level(me, ob);
        return 1;
    }

    if( (query("set_skill/level", ob)+(how/50))>900 )
    {
        message("vision", YEL + ob->name(1) + "摇头道：你付的钱太多了，我的"
                              "技能等级最多不能超过九百级。\n", me,
                                            ({ environment(me), ob }));
        ask_huyuan_level(me, ob);
        return 1;
    }

    gold->add_amount(-how);
    addn("set_skill/level", how/50, ob);
    FACTION_D->gen_npc(ob,query("generation_skill/name", ob));
    ob->save();
    ob->restore();
    house=query("house/"+query("type", me), ob);
    value  = house["value"] + how;
    house += ([ "value" : value, ]);
    me->save();
    message_vision("$N想了想，有点犹豫地从身上掏出"HIY + chinese_number(how) +
                   "两黄金"NOR"，递给了" + ob->name(1) + "。\n"
                   HIC "\n\t" + ob->name(1) + "因为获得了"
                       "黄金升级，技能等级提高了！\n\n" NOR, me);
    ask_huyuan_level(me, ob);
    return 1;
}

//管理者可查询护院的当前技能等级
public int ask_huyuan_level(object me, object ob)
{
    if(!ob->is_livings())
        return notify_fail("嗯....你得先把" + ob->name(1) + "弄醒再说。\n");

    if(ob->is_fighting())
    {
        message_vision("$N对$n摇头道：有什么事等我打完架再说。\n", ob, me);
        return 1;
    }

    if( query("id", me) != query("owner", ob) && !wizardp(me) )
    {
        message_vision("$N对$n摇头道：这些不是你可以随便询问的。\n", ob, me);
        return 1;
    }

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "嘀咕了几句。\n", environment(me), ({ me, ob }));

    tell_object(me, HIW + ob->name(1) + "悄悄的告诉你：我目前的技能等级为"
                    HIY+chinese_number(query("set_skill/level", ob)));

    if( query("set_skill/level", ob) >= 900 )
    {
        tell_object(me, HIW "级，已达最高限度。\n" NOR);
    }
    else
    {
        tell_object(me, HIW "级，尚有升级余地。\n" NOR);
        message("vision", HIC + ob->name(1) + "悄声又道：每付"
                          HIY "五十两黄金" HIC "可以让我提升一级，"
                          "最高可到" HIR "九百" HIC "级。\n" NOR, me,
                                                ({ environment(me), ob }));
    }

    return 1;
}

//管理者拥有一次更改护院所使用的技能的权限
public int set_huyuan_skill(string arg, object me, object ob)
{
    object obj;
    string who, skill;

    if(!arg || sscanf(arg, "%s use %s", who, skill) != 2)
        return notify_fail(HIW "指令格式：setskill <护院ID> "
                               "use <技能名称>\n" NOR);

    obj = present(who, environment(me));
    if(!objectp(obj))
        return notify_fail(YEL "你要设定谁的技能？\n" NOR);

    if( query("id", obj) != query("id", ob) )
        return notify_fail(YEL "你只能为自己的护院设定技能。\n" NOR);

    if( query("owner", obj) != query("id", me) )
        return notify_fail(YEL + obj->name(1) + "并不是你的护院，"
                                "你无权设定其技能。\n" NOR);

    if(!obj->is_livings())
        return notify_fail("嗯....你得先把" + obj->name(1) + "弄醒再说。\n");

    if(obj->is_fighting())
        return notify_fail("嗯....你得先等" + obj->name(1) + "打完架再说。\n");

    if( query("set_skill/owner", obj) == query("id", me) )
        return notify_fail(YEL + "你已经为" + obj->name(1) +
                                 "设定过技能了，无法再次更改。\n" NOR);

    if( query("generation_skill/name", obj) == skill )
        return notify_fail(YEL + obj->name(1) + "当前使用的技能正是「"
                               + skill + "」，无须重复设定。\n" NOR);

    FACTION_D->show_skill(me, skill);

    if( !query_temp("query_faction", me) )
        return 1;
    else
    {
        tell_object(me, HIC "\n你确定要将"HIW + obj->name(1) +
                        HIC"的技能更改为「"HIY + skill +
                        HIC"」吗(y/n)？\n" NOR);
        input_to("confirm_setskill", me, obj);
        return 1;
    }
}

//确认更改护院的技能
public void confirm_setskill(string yn, object me, object ob)
{
   string arg=query_temp("query_faction", me);

    if(!arg)
    {
        tell_object(me, HIR "参数传递错误，技能名称不明。\n" NOR);
        return;
    }

    if(yn == "" || (yn[0] != 'y' && yn[0] != 'Y'))
    {
        tell_object(me, YEL "你改变主意，决定不将" + ob->name(1) +
                            "的技能设定为「" + arg + "」了。\n" NOR);
        delete_temp("query_faction", me);
        return;
    }
    else
    {
        FACTION_D->gen_npc(ob, arg);
        set("set_skill/owner",query("id",  me), ob);
        ob->save();
        tell_object(me, HIG "\n你将"HIW + ob->name(1) + HIG"的技能设定为了「"
                        HIY + arg + HIG"」，今后不再更改。\n" NOR);
        delete_temp("query_faction", me);
        return;
    }
}

//随机产生一个密码，用于保护转让、拆除的安全，可供外部程序调用
public string random_generation_password(int passlen)
{

    int i, dictlen;
    string passstr, dictionary;

    passstr = "";
    dictionary = "1234567890";
    dictionary += "abcdefghijklmnopqrstuvwxyz";
    dictionary += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    dictionary += "!@#$%^&*()_-+=\|/?,.:'";
    dictlen = strlen(dictionary);

    if(!passlen || passlen == 0)
        passlen = random(4) + 5;    // '5' is min password string length

    for(i = 0; i < passlen; i++)
    {
        passstr += sprintf("%c", dictionary[random(dictlen)]);
    }
    return passstr;
}
