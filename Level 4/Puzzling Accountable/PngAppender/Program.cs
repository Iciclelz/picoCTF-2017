using System.IO;
using System.Linq;

namespace PngAppender
{
    class Program
    {
        static void Main(string[] args)
        {
            var b = File.ReadAllBytes(@"C:\Users\Xariru\Desktop\picoCTF 2017\Puzzlingly Accountable\test\SoV1xW80.png").ToList();
                
            b.Insert(0, 10);
            b.Insert(0, 26);
            b.Insert(0, 10);
            b.Insert(0, 13);
            b.Insert(0, 71);
            b.Insert(0, 78);
            b.Insert(0, 80);
            b.Insert(0, 137);

            File.WriteAllBytes(@"C:\Users\Xariru\Desktop\picoCTF 2017\Puzzlingly Accountable\test\flag.png", b.ToArray());
        }
    }
}
