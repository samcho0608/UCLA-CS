import argparse
import random, sys

class randline:
    def __init__(self, filename, high=None):
        if high is not None:
            self.lines = []
            for i in range(filename, high + 1):
                self.lines.append(str(i) + '\n')
        else:
            if filename == '-' or filename is None:
                input_file = sys.stdin
            else:
                input_file = filename
            self.lines = input_file.readlines()

    def chooselines(self):
        # create random permutation of the input file lines
        return random.sample(self.lines, len(self.lines))

    def length(self):
        return len(self.lines)

def main():
    usage_msg = """%(prog)s [OPTION]... FILE

Output randomly selected lines from FILE."""


    parser = argparse.ArgumentParser(usage=usage_msg, description="Output random permutation of lines")
    parser.add_argument("-i", "--input-range=LO-HI", 
                        help="input the range of lines you want to extract random line from", nargs=1, dest="ir",type=str)
    parser.add_argument("-n", "--head-count", help="input number of random lines you want to print out", default=sys.maxsize, dest="numlines")
    parser.add_argument("-r", "--repeat", help="repeat printing out random lines", action='store_true', default=False, dest="repeat")
    parser.add_argument("file", nargs='*', type=argparse.FileType('r'))
    
    args = parser.parse_args(sys.argv[1:]) 
    # try to convert the string into an int
    try:
        numlines = int(args.numlines)
    # when exception thrown, output error
    except:
        parser.error("invalid NUMLINES: {0}".format(args.numlines))
    # if specified numlines is negative
    if numlines < 0:
        parser.error("negative count: {0}".format(args.numlines))

    if args.file is not None and len(args.file) > 1:
        parser.error("wrong number of operands")

    # if both ir and file are passed in
    if args.ir is not None and args.file:
        parser.error("Segmentation Fault")
    
    # if -i was called
    if args.ir is not None:
        try:
            ir_range = args.ir[0].split('-')
            LO = int(ir_range[0])
            HI = int(ir_range[1])
        except:
            parser.error("Invalid Input Range: {0}".format(args.ir[0]))
        # if the number of argument is not 1, output error
        if HI < LO or LO < 0:
            parser.error("Invalid Input Range: {0}".format(args.ir[0]))

        generator = randline(LO, HI)

    else:
        if not args.file:
            generator = randline(None)
        else:
            generator = randline(args.file[0])
    cycle = 0

    # repeat printing permutations    
    # outer loop for the repeating cycle
    # inner loop for printing out the lines in the file
    
    numLinesMet = False
    if numlines == 0:
        numLinesMet = True
    while not numLinesMet:
        # for every new cycle, create a new permutation
        randPerm = generator.chooselines()
        # while numlines is not met, loop through randPerm and print out lines
        for i in range(generator.length()):
            sys.stdout.write(randPerm[i])
            # break when numlines met
            if ( cycle * generator.length() + i + 1 ) == numlines:
                numLinesMet = True
                break
        if not args.repeat:
            break
        else:
            # conditionally done bc if not cycle will be infinitely big
            if numlines > generator.length():
                cycle += 1
        

if __name__ == "__main__":
    main()
