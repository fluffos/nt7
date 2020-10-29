// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("谁杀了我[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "我又杀了谁[2;37;0m
它是王诈的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wangzha");
        set("owner_name", "王诈");
        set_temp("owner", "wangzha");
        set_temp("owner_name", "王诈");
        ::setup();
}
