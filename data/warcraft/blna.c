// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火麒麟[2;37;0m
它是霸王别姬的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "blna");
        set("owner_name", "霸王别姬");
        set_temp("owner", "blna");
        set_temp("owner_name", "霸王别姬");
        ::setup();
}
