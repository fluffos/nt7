// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("谜幻乐团[2;37;0m[2;37;0m", ({"imaginedragon"}));        
        set("gender", "男性");                
        set("long", "美国新秀[2;37;0m
它是笑话的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "joke");
        set("owner_name", "笑话");
        set_temp("owner", "joke");
        set_temp("owner_name", "笑话");
        ::setup();
}
