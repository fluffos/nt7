// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[34m穷奇熊[2;37;0m[2;37;0m", ({"gaze"}));        
        set("gender", "男性");                
        set("long", "桶桶[2;37;0m
它是姜萍萍的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jpvani");
        set("owner_name", "姜萍萍");
        set_temp("owner", "jpvani");
        set_temp("owner_name", "姜萍萍");
        ::setup();
}
