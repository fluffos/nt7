// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m叽咕[2;37;0m[2;37;0m[2;37;0m", ({"jigu"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIG$叽咕$NOR$[2;37;0m
它是叽叽咕咕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mutter");
        set("owner_name", "叽叽咕咕");
        set_temp("owner", "mutter");
        set_temp("owner_name", "叽叽咕咕");
        ::setup();
}
