// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m星际战舰[2;37;0m[2;37;0m", ({"enterprise"}));        
        set("gender", "男性");                
        set("long", "谢晓峰的联邦星舰进取号[2;37;0m
它是谢晓峰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xie");
        set("owner_name", "谢晓峰");
        set_temp("owner", "xie");
        set_temp("owner_name", "谢晓峰");
        ::setup();
}
