void test()
{
        tell_object(find_player("lonely"), "\ncallout被调用！\n\n");
}
int find_handle()
{
        int handle;

        handle = call_out("test", 10);
        return handle;
}
void dt(int handle)
{
        remove_call_out(handle);
}
