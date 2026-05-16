using System;
using System.Runtime.InteropServices;

public class ConnectFour : IDisposable
{
    private IntPtr game;

    private const string DLL = "connect_four_ffi";

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr game_new();

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern void game_free(IntPtr game);

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern int game_make_move(IntPtr game, int col);

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern int game_get_current_player(IntPtr game);

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern int game_is_over(IntPtr game);

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr game_to_string(IntPtr game);

    [DllImport(DLL, CallingConvention = CallingConvention.Cdecl)]
    private static extern void free_string(IntPtr str);

    [DllImport("connect_four_ffi", CallingConvention = CallingConvention.Cdecl)]
    private static extern void game_reset(IntPtr game);

    public ConnectFour()
    {
        game = game_new();
    }

    public int PlayMove(int col)
    {
        return game_make_move(game, col);
    }

    public int CurrentPlayer()
    {
        return game_get_current_player(game);
    }

    public bool IsGameOver()
    {
        return game_is_over(game) != 0;
    }

    public void Reset()
    {
        game_reset(game);
    }

    public string Board()
    {
        IntPtr ptr = game_to_string(game);
        string result = Marshal.PtrToStringAnsi(ptr) ?? "";
        free_string(ptr);
        return result;
    }

    public void Dispose()
    {
        if (game != IntPtr.Zero)
        {
            game_free(game);
            game = IntPtr.Zero;
        }
    }
}