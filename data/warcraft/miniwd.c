// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m青龙[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "女性");                
        set("long", "四大神兽之青龙[2;37;0m
它是妩媚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "miniwd");
        set("owner_name", "妩媚");
        set_temp("owner", "miniwd");
        set_temp("owner_name", "妩媚");
        ::setup();
}
