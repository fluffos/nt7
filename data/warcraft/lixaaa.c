// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红[2;37;0m[2;37;0m", ({"xiaohong"}));        
        set("gender", "女性");                
        set("long", "诚实可爱的小母麒麟[2;37;0m
它是雨雪飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lixaaa");
        set("owner_name", "雨雪飞");
        set_temp("owner", "lixaaa");
        set_temp("owner_name", "雨雪飞");
        ::setup();
}
