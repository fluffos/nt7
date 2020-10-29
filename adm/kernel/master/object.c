// This program is a part of NT MudLIB

// When an object is destructed, this function is called with every
// item in that room.  We get the chance to save users from being destructed.
// 环境遭到毁灭时, 所有内在物件都会呼叫此函式
void destruct_env_of(object ob)
{
        if( interactive(ob) )
        {
                tell_object(ob, "你所在的空间消失了，你现在身处在空虚缥缈之中。\n");
                ob->move(VOID_OB);
        }
}
