// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("没有[2;37;0m[2;37;0m", ({"moyou"}));        
        set("gender", "女性");                
        set("long", "什么都是没有的[2;37;0m
它是胡理胡徒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hulihutu");
        set("owner_name", "胡理胡徒");
        set_temp("owner", "hulihutu");
        set_temp("owner_name", "胡理胡徒");
        ::setup();
}
