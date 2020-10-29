// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m青见[2;37;0m[2;37;0m", ({"zzzz"}));        
        set("gender", "女性");                
        set("long", "长得再靓也是我醜的坐骑[2;37;0m
它是酉鬼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yougui");
        set("owner_name", "酉鬼");
        set_temp("owner", "yougui");
        set_temp("owner_name", "酉鬼");
        ::setup();
}
