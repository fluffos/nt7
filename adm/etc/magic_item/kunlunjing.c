// 上古十大神器之 昆仑镜
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// 可穿梭的地点
mapping place = ([
        "beijing"   : "/d/beijing/majiu",
        "yangzhou"  : "/d/city/majiu",
        "dali"      : "/d/dali/majiu",
        "foshan"    : "/d/foshan/majiu",
        "fuzhou"    : "/d/fuzhou/majiu",
        "guanwai"   : "/d/guanwai/majiu",
        "hangzhou"  : "/d/hangzhou/majiu",
        "lanzhou"   : "/d/lanzhou/majiu",
        "lingzhou"  : "/d/lingzhou/majiu",
        "luoyang"   : "/d/luoyang/majiu",
        "yongdeng"  : "/d/huanghe/majiu",
        "suzhou"    : "/d/suzhou/majiu",
        "xiangyang" : "/d/xiangyang/majiu",
        "yili"      : "/d/xingxiu/majiu",
        "chengdu"   : "/d/city3/majiu",
        "emei"      : "/d/emei/majiu1",
        "emei2"     : "/d/emei/majiu2",
        "quanzhou"  : "/d/quanzhou/majiu1",
        "jiaxing"   : "/d/quanzhou/majiu2",
        "jingzhou"  : "/d/jingzhou/majiu",
        "nanyang"   : "/d/shaolin/majiu1",
        "changan"   : "/d/changan/majiu",
        "wugong"    : "/d/quanzhen/majiu",
        "hengyang"  : "/d/henshan/majiu",
        "kaifeng"   : "/d/kaifeng/majiu",
        "kunming"   : "/d/kunming/majiu",
        "zhongzhou" : "/d/zhongzhou/majiu",

]);

void create()
{
        set_name(HIW "昆仑镜" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "面");
                set("long", HIW "这是一面通体银光的镜子，据说拥有穿梭时空的能力。\n"                               
                                "可借用其穿梭(trans)到各大城市马厩，可以输入 trans 查看\n"
                                "可穿梭的地点，使用 trans ? 查看使用次数。\n" NOR);                

        }

        setup();
}

void init()
{
        add_action("do_trans", "trans");
}

int do_trans(string arg)
{
        object me;
        string *places;
        int i;
        
        me = this_player();
        
        if(! objectp(present("kunlun jing", me)))return 0;
                
        places = keys(place);
        if (! arg)
        {
              write(HIC "你可以穿梭到以下地点：\n");
              for (i = 0; i < sizeof(places); i ++)
                      write(places[i] + "\n");
              
              return 1;
        }
        if (arg == "?")
        {
                 write(HIG "使用次数 " + this_object()->query("count") + "/30\n" NOR);
                 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
                         
        if (member_array(arg, places) == -1)
                 return notify_fail("看清楚，没有你要到的地方。\n");                

        message_sort(HIW "\n$N" HIW "挥舞着手中的昆仑镜，刹那间光华万道，$N" HIW "借"
                         "着万道光芒消失在天际 ……\n" NOR, me);

        write(HIG "你从天而下，落在了地上。\n" NOR);
        
        me->move(place[arg]);        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 30)
        {
                write(HIW "只听得一阵清脆的破碎声，昆仑镜已经损坏了！\n" NOR);
                destruct(this_object());                                
        }
        
        return 1;
}
