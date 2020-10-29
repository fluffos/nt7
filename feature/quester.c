// quester.c 接收请求任务
#include <ansi.h>

int is_quester() { return 1; }

/*
// 接受询问
mixed accept_ask(object who, string topic)
{
        return QUEST_D->accept_ask(this_object(), who, topic);
}
*/
// 请求任务
int ask_quest(object who)
{
        return QUEST_D->ask_quest(this_object(), who);
}

/*
int ask_defend(object who)
{
        return QUEST_D->ask_defend(this_object(), who);
}
*/

int ask_finish(object who)
{
        return QUEST_D->ask_finish(this_object(), who);
}
/*
// 接收物品
int accept_object(object who, object ob)
{
        return QUEST_D->accept_object(this_object(), who, ob);
}
*/

// 取消任务
int cancel_quest(object who)
{
        return QUEST_D->cancel_quest(this_object(), who);
}

/*
void die()
{
        this_object()->full_self();
        return;
}

void unconcious()
{
        this_object()->full_self();
        return;
}
*/

