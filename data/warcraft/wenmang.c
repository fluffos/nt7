// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m琴[1;37m棋[1;33m书[1;31m画[2;37;0m[2;37;0m", ({"taixuanjing"}));        
        set("gender", "女性");                
        set("long", "这是文盲的必备法宝。[2;37;0m
它是文盲的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wenmang");
        set("owner_name", "文盲");
        set_temp("owner", "wenmang");
        set_temp("owner_name", "文盲");
        ::setup();
}
