// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m神秘货[1;37m[5m[2;37;0m[2;37;0m", ({"xxman"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIW$神秘货$HIW$$BLINK$[2;37;0m
它是神秘人物的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xman");
        set("owner_name", "神秘人物");
        set_temp("owner", "xman");
        set_temp("owner_name", "神秘人物");
        ::setup();
}
