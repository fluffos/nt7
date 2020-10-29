// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m马杀鸡[2;37;0m[2;37;0m", ({"hitall"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是杀马特的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "killall");
        set("owner_name", "杀马特");
        set_temp("owner", "killall");
        set_temp("owner_name", "杀马特");
        ::setup();
}
