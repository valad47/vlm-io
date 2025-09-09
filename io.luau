local io = {}
      io.LOAD_SO = true
      io.SO_PREFIX = "vlm_"

function io.WriteFile(filename: string, data: string): () end
function io.ReadFile(filename: string): string end
function io.DeleteFile(filename: string): () end
function io.write(...) end
function io.flush() end
function io.system() end
function io.shcall() end

function io.fopen() end
function io.fread() end
function io.fwrite() end
function io.fclose() end

return io