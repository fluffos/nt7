// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小瞌睡虫[2;37;0m[2;37;0m", ({"sleepbug"}));        
        set("gender", "男性");                
        set("long", "大梦方觉晓！[2;37;0m
它是卓一航的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zhuoyi");
        set("owner_name", "卓一航");
        set_temp("owner", "zhuoyi");
        set_temp("owner_name", "卓一航");
        ::setup();
}
