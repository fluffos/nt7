// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m风间萌衣[2;37;0m[2;37;0m", ({"wurisa"}));        
        set("gender", "女性");                
        set("long", "wield jian[2;37;0m
它是宇智波鼬的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wukgdile");
        set("owner_name", "宇智波鼬");
        set_temp("owner", "wukgdile");
        set_temp("owner_name", "宇智波鼬");
        ::setup();
}
