// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"cnn"}));        
        set("gender", "男性");                
        set("long", "这个是条龙[2;37;0m
它是绻阆氚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ccav");
        set("owner_name", "绻阆氚");
        set_temp("owner", "ccav");
        set_temp("owner_name", "绻阆氚");
        ::setup();
}
