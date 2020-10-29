// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白玉麒麟[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只雪白的麒麟[2;37;0m
它是王动的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wangdong");
        set("owner_name", "王动");
        set_temp("owner", "wangdong");
        set_temp("owner_name", "王动");
        ::setup();
}
