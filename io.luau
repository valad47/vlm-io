local io = {}
      io.LOAD_SO = true
      io.SO_PREFIX = "vlm_"

function io.WriteFile(filename: string, data: string): () end
function io.ReadFile(filename: string): string end
function io.write(...) end
function io.system() end
function io.shcall() end

return io