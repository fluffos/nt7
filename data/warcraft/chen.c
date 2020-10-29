// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m星辰[2;37;0m[2;37;0m", ({"cnn"}));        
        set("gender", "女性");                
        set("long", "一只威严冷酷的纯白大虎，眼睛里透出绿幽幽的光芒。[2;37;0m
它是游戏人生的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "chen");
        set("owner_name", "游戏人生");
        set_temp("owner", "chen");
        set_temp("owner_name", "游戏人生");
        ::setup();
}
