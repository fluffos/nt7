// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m叽喳[2;37;0m[2;37;0m[2;37;0m", ({"jizha"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIG$叽喳$NOR$[2;37;0m
它是叽叽喳喳的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "twitter");
        set("owner_name", "叽叽喳喳");
        set_temp("owner", "twitter");
        set_temp("owner_name", "叽叽喳喳");
        ::setup();
}
