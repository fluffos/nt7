inherit F_CLEAN_UP;
int idx;

int main(object me, string arg)
{
        object env, *inv;

        idx +=1;
        write((string)idx + "\n");

        if(!me || !objectp(env = environment(me)))
                return 0;

        if(!function_exists("cmd_dig_function", env))
                return notify_fail("你四处看了看，发现这里没什么可以挖掘的地方。\n");

        if(!sizeof( inv = filter_array(all_inventory(me),
                (: $1->is_mine_tool() && $1->tool_can_use() :)) ) )
                return notify_fail("你身上没有用于挖掘的工具。\n");

        inv[0]->use_this_tool();

        notify_fail("你四处挖了挖，什么也没有挖出来。\n");
        return env->cmd_dig_function(me, arg);
}
